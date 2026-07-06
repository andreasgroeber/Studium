;(load "C:\\Users\\groeb\\Desktop\\Schule\\CLIPS\\Belegv2_A_Groeber.lisp")

;default strassen koennen hier angepasst werden
;;----------------------------------------------------------------------------
(defvar *street1*
  (loop for x from 0 to 100
        collect (cons x 50)
  )
)

(defvar *street2*
  (loop for y from 0 to 100
        collect (cons 35 y)
  )
)

(defun streets-intersect-p (street1 street2)
  (let ((intersection (intersection street1 street2 :test #'equal)))
    (when intersection
      (format t "Die Strassen treffen sich an folgenden Punkten:~%")
      (dolist (point intersection)
        (format t "~a~%" point)))))

(streets-intersect-p *street1* *street2*)


;; Definition der symbolischen Knoten Punkte  +++ muss an strassennetz angepasst werden!
(defvar *oben* '(35 100 :down))
(defvar *unten* '(35 0 :up))
(defvar *links* '(0 50 :right))
(defvar *rechts* '(100 50 :left))

;;----------------------------------------------------------------------------

;(defun draw-map (street1 street2)
;  (loop for y from 100 by 5 downto 0 do
;        (format t "~3d   " y)
;        (loop for x from 0 to 100 by 5 do
;              (if (member (cons x y) street1 :test #'equal)
;                  (format t "x ")
;                  (if (member (cons x y) street2 :test #'equal)
;                      (format t "x ")
;                      (format t ". "))))
;        (format t "~%"))
;  (format t "   ")
;  (format t "   0            35                          100")
;)

;;streets ende
;;-------------------------------------------------------------------------------------------------------------------------
;;vehicle start

(defstruct vehicle
  x
  y
  direction
  type
  speed
  id)

(defvar *next-vehicle-id* 1)
(defvar *vehicles* nil)

(defun spawn-vehicle (x y direction type)
  "Erzeugt ein neues Fahrzeug und platziert es auf den Strassen."
  (let* ((speed (if (eq type 'lkw) 4 5)) ;; Geschwindigkeit je nach Typ setzen
         (vehicle (make-vehicle :x x :y y :direction direction :type type :id *next-vehicle-id* :speed speed)))
    (push vehicle *vehicles*)
    (incf *next-vehicle-id*)
    vehicle))

(defun spawn-vehicle-from-point (spawn-point type)
  (destructuring-bind (x y direction) spawn-point
    (spawn-vehicle x y direction type)))


(defun move-vehicle (vehicle)
  "Bewegt ein Fahrzeug gemaess seiner Richtung und Geschwindigkeit."
  (let* ((next-x (vehicle-x vehicle))
         (next-y (vehicle-y vehicle)))
  
    (case (vehicle-direction vehicle)
      (:right (incf next-x (vehicle-speed vehicle)))
      (:left (decf next-x (vehicle-speed vehicle)))
      (:up (incf next-y (vehicle-speed vehicle)))
      (:down (decf next-y (vehicle-speed vehicle))))
    
    ;; ueberpruefen, ob das Fahrzeug im naechsten Schritt ueber die Position 35 50 hinausfahren wuerde
    (when (and (overlaps-next-position-p vehicle 35 50)
               (not (green-light-p 35 50)))
      (format t "Fahrzeug ~a (Typ: ~a) kann nicht weiterfahren wegen roter Ampel an Position (35, 50).~%"
              (vehicle-id vehicle)
              (vehicle-type vehicle))
      )
    
    ;; Fahrzeug nur bewegen, wenn keine Einschraenkungen (durch rote Ampel)
    (unless (and (overlaps-next-position-p vehicle 35 50)
                 (not (green-light-p 35 50)))
      (setf (vehicle-x vehicle) next-x)
      (setf (vehicle-y vehicle) next-y)))
)

(defun overlaps-next-position-p (vehicle x y)
  "Ueberprueft, ob das Fahrzeug im naechsten Schritt ueber die Position (x, y) hinausfahren wuerde."
  (let ((next-x (vehicle-x vehicle))
        (next-y (vehicle-y vehicle)))
    (case (vehicle-direction vehicle)
      (:right (incf next-x (vehicle-speed vehicle)))
      (:left (decf next-x (vehicle-speed vehicle)))
      (:up (incf next-y (vehicle-speed vehicle)))
      (:down (decf next-y (vehicle-speed vehicle))))
    (and (> next-x x)
         (> next-y y))))



(defun draw-vehicles ()
  "Zeichnet alle Fahrzeuge auf den Strassen."
  (format t "Fahrzeuge auf den Strassen:~%")
  (loop for vehicle in *vehicles* do
        (format t "Fahrzeug ~a (Typ: ~a, Geschwindigkeit: ~d) an Position (~d, ~d) bewegt sich ~a~%"
                (vehicle-id vehicle)
                (vehicle-type vehicle)
                (vehicle-speed vehicle)
                (vehicle-x vehicle)
                (vehicle-y vehicle)
                (vehicle-direction vehicle)))
  (format t "~%"))

;; ueberpruefen ob fahrzeug noch auf relevanten strassen 

(defun vehicle-on-street-p (vehicle street1 street2)
  "Ueberprueft, ob sich ein Fahrzeug auf einer der beiden Strassen befindet."
  (or (member (cons (vehicle-x vehicle) (vehicle-y vehicle)) street1 :test #'equal)
      (member (cons (vehicle-x vehicle) (vehicle-y vehicle)) street2 :test #'equal)))

(defun vehicle-outside-bounds-p (vehicle)
  "Ueberprueft, ob ein Fahrzeug die Strassenbegrenzung ueberschritten hat."
  (or (< (vehicle-x vehicle) 0) (> (vehicle-x vehicle) 100)
      (< (vehicle-y vehicle) 0) (> (vehicle-y vehicle) 100)))

(defun remove-off-road-vehicles ()
  "Entfernt alle Fahrzeuge, die sich nicht mehr auf den Strassen befinden, aus der Liste der Fahrzeuge."
  (setf *vehicles*
        (remove-if-not (lambda (vehicle)
                         (cond
                           ((vehicle-outside-bounds-p vehicle)
                            (format t "Fahrzeug ~a (Typ: ~a) hat die Strassenbegrenzung ueberschritten und wird entfernt.~%"
                                    (vehicle-id vehicle)
                                    (vehicle-type vehicle))
                            nil)
                           ((not (vehicle-on-street-p vehicle *street1* *street2*))
                            (format t "Fahrzeug ~a (Typ: ~a) ist von der Strasse abgekommen und wird entfernt.~%"
                                    (vehicle-id vehicle)
                                    (vehicle-type vehicle))
                            nil)
                           (t t)))
                       *vehicles*))
)

;vehicle end
;;-----------------------------------------------------------------------------------------------------------------------------------
;Ampel Start

(defvar *traffic-light-state* :street1) ;; :street1 bedeutet gruen fuer Strasse 1, rot fuer Strasse 2
(defvar *time-since-last-switch* 0)
(defvar *switch-interval* 3) ;; Anzahl der Zeitschritte bis zum Umschalten

(defun switch-traffic-light ()
  "Schaltet die Ampel um."
  (setf *traffic-light-state* (if (eq *traffic-light-state* :street1) :street2 :street1))
  (format t "Ampel schaltet auf ~a~%" *traffic-light-state*)
  (setf *time-since-last-switch* 0))

  (defun vehicle-at-intersection-p (vehicle)   ;; !!! wichtig hier den Kreuzungspunkt anpassen wenn sich strassen netz aendert!
  "Ueberprueft, ob ein Fahrzeug an der Kreuzung (35, 50) ist."
  (and (= (vehicle-x vehicle) 35) (= (vehicle-y vehicle) 50)))

(defun vehicle-can-move-p (vehicle)
  "Ueberprueft, ob ein Fahrzeug entsprechend der aktuellen Ampel fahren darf."
  (or (not (vehicle-at-intersection-p vehicle))
      (case *traffic-light-state*
        (:street1 (or (eq (vehicle-direction vehicle) :right) (eq (vehicle-direction vehicle) :left)))
        (:street2 (or (eq (vehicle-direction vehicle) :up) (eq (vehicle-direction vehicle) :down))))))



(defun green-light-p (x y)
  "Gibt zurueck, ob die Ampel an der Position (x, y) gruen ist."
  (let ((current-time (get-universal-time)))
    (if (evenp current-time)
        t  ; Gerade Sekunden: Gruenes Licht
        nil)))  ; Ungerade Sekunden: Rotes Lich

(defun move-vehicles-with-traffic-light ()
  "Bewegt die Fahrzeuge entsprechend ihrer Richtung und der Ampelsteuerung."
  (dolist (vehicle *vehicles*)
    (when (vehicle-can-move-p vehicle)
      (case (vehicle-direction vehicle)
        (:right (incf (vehicle-x vehicle) (vehicle-speed vehicle)))
        (:left (decf (vehicle-x vehicle) (vehicle-speed vehicle)))
        (:up (incf (vehicle-y vehicle) (vehicle-speed vehicle)))
        (:down (decf (vehicle-y vehicle) (vehicle-speed vehicle)))))))

;----------------------------------------
; Zeitschritte



(defun +time (time)
  "Simuliert die Zeit, indem es die Fahrzeuge auf den Strassen fuer die angegebene Zeit bewegt."
  (loop repeat time do
        (move-vehicles-with-traffic-light)
        (incf *time-since-last-switch*)  ; Zeit seit dem letzten Zeitschritt erhoehen
        (when (>= *time-since-last-switch* *switch-interval*)
          (switch-traffic-light)) ; Ampel umschalten, wenn das Intervall erreicht ist
  )  
    (remove-off-road-vehicles)                            
    (draw-vehicles)
)

(streets-intersect-p *street1* *street2*)
;(draw-map *street1* *street2*)


;------------------------------------------------- Neue Funktionalitaeten --------------------------------------------

(defun adjust-lkw-position (x)
  "Passt die Position eines LKWs an die Karten-Aufloesung."
  (cond ((< x 35) (- x (mod x 5)))
        ((> x 35) (+ x (- 5 (mod x 5))))
        (t x)))

(defun get-adjusted-position (vehicle)
  "Gibt die angepasste Position eines Fahrzeugs zurueck."
  (let ((x (vehicle-x vehicle))
        (y (vehicle-y vehicle)))
    (if (eq (vehicle-type vehicle) 'lkw)
        (cons (adjust-lkw-position x) (adjust-lkw-position y))
        (cons x y))))

(defun draw-map (street1 street2 vehicles)
  (let ((vehicle-positions (make-hash-table :test 'equal)))
    ;; Fahrzeugpositionen in einer Hash-Tabelle speichern
    (dolist (vehicle vehicles)
      (let ((pos (get-adjusted-position vehicle)))
        (push (vehicle-id vehicle) (gethash pos vehicle-positions))))
    
    ;; Karte zeichnen
    (loop for y from 100 by 5 downto 0 do
          (format t "~3d   " y)
          (loop for x from 0 to 100 by 5 do
                (let ((pos (cons x y)))
                  (cond
                    ((member pos street1 :test #'equal)
                     (if (gethash pos vehicle-positions)
                         (let ((ids (gethash pos vehicle-positions)))
                           (if (> (length ids) 1)
                               (format t "~{~a~^+~} " ids)
                               (format t "~a " (first ids))))
                         (format t "x ")))
                    ((member pos street2 :test #'equal)
                     (if (gethash pos vehicle-positions)
                         (let ((ids (gethash pos vehicle-positions)))
                           (if (> (length ids) 1)
                               (format t "~{~a~^+~} " ids)
                               (format t "~a " (first ids))))
                         (format t "x ")))
                    (t
                     (format t ". ")))))
          (format t "~%"))
    (format t "   ")
    (format t "   0            35                          100")
  )
)

(defun print-map ()
  (draw-map *street1* *street2* *vehicles*)
)


(defun simulate-time (time)
  "Simuliert die Zeit und gibt den Zustand der Simulation aus."
  (setq *count* 1)
  (loop repeat time do
        (move-vehicles-with-traffic-light)
        (incf *time-since-last-switch*)
        (when (>= *time-since-last-switch* *switch-interval*)
          (switch-traffic-light)) ; Ampel umschalten, wenn das Intervall erreicht ist
        
        ;; Ausgabe
        (format t "Zeitschritt ~d:~%" *count*)
        (incf *count*)
        (format t "~%--------------------------------~%")
        (format t "Ampel:~%")
        (format t "Ampelzustand: ~a~%" *traffic-light-state*)
        (format t "Zeitschritt (bis Wechsel): ~d / ~d~%"  *time-since-last-switch* *switch-interval*)
        (format t "~%--------------------------------~%")
        (format t "Vehicles:~%")
        (remove-off-road-vehicles)
        (draw-vehicles)
        (format t "~%--------------------------------~%")
        (format t "Karte:~%")
        (print-map)
        (format t "~%================================~%")
  )        
)



;Test-Umgebung
;--------------------------------------------------------------------
(print-map) 
(spawn-vehicle 0 50 :right 'pkw)
(spawn-vehicle 0 50 :right 'pkw)
(spawn-vehicle 35 5 :up 'lkw)
(spawn-vehicle-from-point *unten* 'pkw)
(spawn-vehicle 35 65 :right 'lkw)
(simulate-time 10) 
;--------------------------------------------------------------------

; Neue Funktionalitaeten funktionieren
; Die Karte wird aber etwas verschoben/ungenau wenn sich viele Fahrzeuge auf selber Position befinden

;---------------------------------------------Dokumenation------------------------------------------------------------------------------------

; Name: Andreas Groeber
; MatrNr: 47708


;Wichtige Befehle
; (+time <Zeitschritte>) siehe Funktion oben
; (draw-vehicles) Gibt Fahrzeug liste mit Parametern aus
; (spawn-vehicle <x> <y> <direction> <type>) erzeugt ein neues Fahrzeug
; (spawn-vehicle-from-point) erzeugt Fahrzeug von festem Ausgangspunkt --> Fahrzeug faehrt in entgegengesetzte Richtung --> wenn oben erzeugt faehrt es nach unten
; (draw-map *street1* *street2*) um erneut das Strassen "Abbild" ein zu blenden

; Funktionalitaeten
; Es kann eine simple Kreuzung simuliert werden mit beliebig vielen Fahrzeugen, zudem kann zwischen lkw und pkw unterschieden werden (pkw's sind ein bisschen schneller unterwegs)
; Die Strassen koennen etwas schwerfaelliger angepasst werden, da viel vom Schnittpunkt dieser abhaengt
; Fahrzeuge werden entfernt wenn sie von der Strasse abkommen oder ihr "Ziel" erreichen

; Was fehlt / Erweiterungen
; Kollisionsabfrage (im Moment noch nicht vorhanden) man koennte auch sagen das die Strasse viele Spuren hat :)
; Richtungswechsel --> sehr interessant an der Kreuzung aber auch sehr kompliziert 
; Kreisverkehr anstatt Ampel

; Fehler / Bugs
; Es wird geprueft ob ein Fahrzeug am Punkt 35 50 rot oder gruen hat, falls es rot hat bleibt es stehen. Wenn jedoch ein Fahrzeug am Punkt 34 50 steht wird nicht ueberprueft ob es 
; rot hat und es kann weiterfahren selbst wenn dem so waere. Ich habe versucht das ueber ein lookahed-1 zu loesen das hat leider nicht wie gewuenscht funktioniert.   
; Dadurch enstehen die Warnings der rest funktioniert soweit ohne fehler