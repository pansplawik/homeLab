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


### Schemat przepływu danych z czujnika protokołem MQTT
```
                      ESP32 + DHT22 + Moduł WiFI 
                              │
                              ▼
                        Mosquitos (Broker MQTT) 
                              │
                              ▼      
    Telegraf + InfluxDB (Skrapping komunikatów + storage do bazy)
                              │
                              ▼
                 Grafana (wykresy i statystyka)
```

### Schemat przepływu danych z czujnika krótsza droga
```
                      ESP32 + DHT22 + Moduł WiFI 
                              │
                              ▼
          InfluxDB (wgrania danych bezpośrednio do wybrane bucketu)
                              │
                              ▼
                 Grafana (wykresy i statystyka)
```
