# HomeLab - Symulacja infrastruktury IT szpitala

[English abstract here.](/Abstract.md)

## Opis projektu

Projekt przedstawia symulację infrastruktury IT szpitala, obejmującą systemy medyczne (PACS, RIS, HIS), integrację danych (HL7, FHIR, DICOM), monitoring, telemetrykę IoT oraz środowisko hybrydowe.

Celem projektu jest odwzorowanie rzeczywistej architektury systemów medycznych z uwzględnieniem:

- integracji systemów
- przepływu danych medycznych
- niezawodności i monitoringu infrastruktury
- wirtualizacji i konteneryzacji

---

## Architektura

System został zaprojektowany w oparciu o podejście warstwowe:

- **Infrastruktura**: Proxmox VE (KVM, LXC, VM)
- **Aplikacje**: Docker, kontenery LXC
- **Systemy medyczne**: FHIR HIS, Mirth Connect, RIS, PACS (Orthanc)
- **Integracja**: HL7, FHIR, DICOM
- **Monitoring**: Prometheus, Grafana, Loki
- **IoT**: MQTT, ESP32, InfluxDB
- **Backup**: VPS + Nextcloud (zasada 3-2-1)

Szczegółowe schematy:  
[Schematy.md](./Schematy.md)

---

## Technologie

- Proxmox VE (KVM, LXC)
- Docker / Docker Compose
- Mirth Connect
- Orthanc (PACS)
- HL7 / FHIR / DICOM
- Prometheus + Grafana + Loki
- MQTT (Mosquitto)
- InfluxDB
- Nextcloud / Minio (backup)
- Active Directory (Windows Server)

---

## Funkcjonalności

- Symulacja workflow radiologicznego (FHIR → RIS → PACS)
- Integracja danych medycznych (HL7 / FHIR)
- Telemetria IoT (MQTT)
- Centralny monitoring i logowanie
- Środowisko hybrydowe (lokalne + VPS)
- Automatyczny backup danych

---

## Struktura projektu
- `kody/` - skrypty konfiguracyjne użyte przy konfiguowaniu aplikacji oraz do automatyzacji 
- `zdj/` - 
- `*.md` - dokumentacja (FHIR, MQTT, VM, LXC, AD)
- `Schematy.md` - schematy architektury

---

## Dokumentacja

- [FHIR](./FHIR.md)
- [MQTT](./mqtt.md)
- [VM](./VM.md)
- [LXC](./LXC.md)
- [Active Directory](./AD.md)
- [VPS / Backup](./VPS.md)

---

## Cel projektu

Celem projektu jest zrozumienie i przedstawienie sposobu działania, integracji oraz utrzymania nowoczesnych systemów IT w środowisku szpitalnym.