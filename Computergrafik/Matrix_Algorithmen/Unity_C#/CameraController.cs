using UnityEngine;

public class CameraController : MonoBehaviour
{
    public float moveSpeed = 10f;       // Geschwindigkeit für WASD
    public float rotateSpeed = 50f;     // Drehgeschwindigkeit für Pfeiltasten
    public float zoomSpeed = 10f;       // Geschwindigkeit für Zoom (PageUp/PageDown)

    private float yaw = 0f;   // horizontale Rotation
    private float pitch = 0f; // vertikale Rotation

    void Update()
    {
        // Kamerabewegung mit WASD
        float h = Input.GetAxis("Horizontal"); // A/D
        float v = Input.GetAxis("Vertical");   // W/S
        Vector3 move = transform.forward * v + transform.right * h;
        transform.position += move * moveSpeed * Time.deltaTime;

        // Horizontale Rotation (links/rechts Pfeiltasten)
        if (Input.GetKey(KeyCode.LeftArrow))
            yaw -= rotateSpeed * Time.deltaTime;
        if (Input.GetKey(KeyCode.RightArrow))
            yaw += rotateSpeed * Time.deltaTime;

        // Vertikale Rotation (oben/unten Pfeiltasten)
        if (Input.GetKey(KeyCode.UpArrow))
            pitch -= rotateSpeed * Time.deltaTime; // Minus = nach oben
        if (Input.GetKey(KeyCode.DownArrow))
            pitch += rotateSpeed * Time.deltaTime; // Plus = nach unten

        // Begrenzung der vertikalen Rotation
        pitch = Mathf.Clamp(pitch, -90f, 90f);

        // Rotation anwenden
        transform.rotation = Quaternion.Euler(pitch, yaw, 0f);

        // Zoom mit PageUp/PageDown
        if (Input.GetKey(KeyCode.PageUp))
            transform.position += transform.forward * zoomSpeed * Time.deltaTime;
        if (Input.GetKey(KeyCode.PageDown))
            transform.position -= transform.forward * zoomSpeed * Time.deltaTime;
    }
}
