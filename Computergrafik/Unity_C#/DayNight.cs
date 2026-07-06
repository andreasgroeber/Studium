using UnityEngine;

namespace _scripts
{
    public class DayNightCycle : MonoBehaviour
    {
        [Header("Skybox & Licht")]
        [SerializeField] private Material skybox;       // Procedural Skybox
        [SerializeField] private Light sunLight;        // Directional Light als Sonne

        [Header("Einstellungen")]
        [SerializeField] private float dayDuration = 120f; // Dauer eines Tages in Sekunden
        [SerializeField] private float minExposure = 0.15f; // Nacht
        [SerializeField] private float maxExposure = 1f;    // Tag
        [SerializeField] private float minIntensity = 0f;   // Lichtintensität Nacht
        [SerializeField] private float maxIntensity = 1f;   // Lichtintensität Tag

        [Header("Sonnenfarbe")]
        [SerializeField] private Color nightColor = new Color(0.1f, 0.1f, 0.35f);  // Dunkelblau
        [SerializeField] private Color sunriseColor = new Color(1f, 0.5f, 0.2f);   // Orange
        [SerializeField] private Color dayColor = Color.white;                      // Weiß

        private float _time = 0f;
        private static readonly int Rotation = Shader.PropertyToID("_Rotation");
        private static readonly int Exposure = Shader.PropertyToID("_Exposure");


        void Start()
        {
            RenderSettings.skybox = skybox;
        }

        void Update()
        {
            // Zeit fortschreiten lassen
            _time += Time.deltaTime / dayDuration * 360f; // Skaliere auf 360° für volle Rotation
            _time %= 360f; // Wrap-around für sauberen Zyklus

            // Rotation der Skybox
            skybox.SetFloat(Rotation, _time);

            // Belichtung animieren
            float t = Mathf.Sin(_time * Mathf.Deg2Rad) * 0.5f + 0.5f; // 0 = Nacht, 1 = Tag
            float exposure = Mathf.Lerp(minExposure, maxExposure, t);
            skybox.SetFloat(Exposure, exposure);

            // Sonnenlicht drehen
            sunLight.transform.rotation = Quaternion.Euler(_time - 90f, 170f, 0f);

            // Sonnenlicht Intensität anpassen
            sunLight.intensity = Mathf.Lerp(minIntensity, maxIntensity, t);

            // Sonnenfarbe flüssig interpolieren
            if (t < 0.25f) // Nacht → Sonnenaufgang
                sunLight.color = Color.Lerp(nightColor, sunriseColor, t / 0.25f);
            else if (t < 0.5f) // Sonnenaufgang → Tag
                sunLight.color = Color.Lerp(sunriseColor, dayColor, (t - 0.25f) / 0.25f);
            else if (t < 0.75f) // Tag → Sonnenuntergang
                sunLight.color = Color.Lerp(dayColor, sunriseColor, (t - 0.5f) / 0.25f);
            else // Sonnenuntergang → Nacht
                sunLight.color = Color.Lerp(sunriseColor, nightColor, (t - 0.75f) / 0.25f);

        }
    }
}
