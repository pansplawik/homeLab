# Schematyczna prezentacja zagadnień z projektu
## Podział na fizyczne serwery
```
                     [Serwer fizyczny]
                     /       │        \   
                   [VPS]  [Proxmox]   [Nextcloud - Offsite Backup]
```

## Podział na użyte maszyny wirtualne
```
                  ┌──────────────────────────┐
                  │     Maszyny wirtualne    │
                  │                          │
                  │  - Monitoring (Prometheus│
                  │    + Grafana + Loki)     │
                  └──────────────────────────┘
```

## Podział na użyte kontenery
```
                  ┌──────────────────────────┐
                  │      Kontenery (LXC)     │
                  │                          │
                  │  - NGINX oraz Ansible    │
                  │  - FHIR HIS              │
                  │  - Mirth Connect         │
                  │  - Orthanc (PACS)        │
                  └──────────────────────────┘
```

## Schemat przepływu danych radiologicznych
```
            FHIR HIS (skierowanie)
               │
               ▼
          Mirth Connect (generowanie zlecenia do RIS)
               │                       
               ▼                         
           PseudoRIS   (generowanie opisu)          
               │
               ▼
             Mirth   (tworzenie obserwacji oraz opis w formie PDF)
               │                                              \
               ▼                                               ▼
FHIR Observation / DiagnosticReport                           Orthanc PACS
```

## Schemat realizacji backupu
```
                        Każdy LXC / VM
                              │
                              ▼
                  mount WebDAV (ephemeral)
                              │
                              ▼      
                  Nextcloud (Off-site storage)
```

## Wykresy robione w Grafanie
```
                  ┌──────────────────────────┐
                  │      Wykresy (LXC)       │
                  │  - OpenVPN               │
                  │  - Docker                │
                  │  - Orthanc               │
                  │  - NGINX (logs)          │
                  │  - Docker (logs)         │
                  │  - MQTT                  │
                  └──────────────────────────┘
```

### Schemat przeływu logów i metryk
```
                        Agenci exporterzy 
                              │
                              ▼
                        Prometheus + Loki 
                              │
                              ▼      
                       Grafana Dashboard
```
