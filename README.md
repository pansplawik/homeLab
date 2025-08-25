# 🖥️ Portfolio Homelaba – VirtualBox

## 🎯 Cel projektu
- Nauka i ćwiczenie administracji systemami Linux/Windows  
- Testowanie środowisk sieciowych i usług serwerowych  
- Automatyzacja i zarządzanie infrastrukturą wirtualną  
- Symulacja realnego środowiska produkcyjnego  

---

## 💾 Sprzęt i baza
- Laptop/PC: **[model, CPU, RAM, dysk]**  
- System hosta: **Windows**  
- Oprogramowanie: **Oracle VirtualBox + Extension Pack**  

---

## 🗂️ Struktura homelaba

### 🌐 Warstwa sieciowa
- Router/Firewall: **Mikrotik hAP ac^2**  
- Sieci: NAT / Host-only / Internal Network  
- VLAN:
    - 192.168.1.0/24 - skonfigurowana przez router ISP
    - 192.168.80.0/24 - skonfigurowany przez mikrotika 
    - 10.10.0.0/24 - VPN

### 🖧 Serwery bazowe
- **Linux Server (Ubuntu)**  
  - Rola: serwer WWW (Nagios, Bandwidthd), SAMBA
  - Cele:
    - SSH monitoring (z wykorzystaniem konfiguracji wtyczek Nagios, oraz Bandwidthd)

- **Linux Server (Red Hat)**  
  - Rola: serwer WWW (Zabbix)  
  - Cele:
    - Nauka i przyswajanie wiedzy z konfiguracji aplikacji do zarządzania VM
    - wysyłanie maili z raportami oraz błędami
    - wykonywanie regularnego backup-u oraz wysyłanie go do MINIO (funkcjonalność utworzone z wykorzystanem CRON)  

- **Linux Serwer (Ubuntu)**  
  - Rola: Serwer OpenVPN  
  - Cele:
    - nauka tworzenia serwera VPN
    - nauka tworzenia osobnego VLAN-u
    - nauka IPTABLES, ufw oraz ip 
    - nauka tworzenia połączenia dwuskładniowego

- **Windows 11**  
  - Rola: serwer PACS połączony z nanoRIS
  - Cele:
    - stworzenie PACS z wykorzystaniem DICOM Conquest
    - integracja z Mirth Connect 4.5.2 (Pełni funkcję nanoRIS)

- **Linux Serwer (MINIO)**  
  - Rola: twierdza danych  
  - Cele:
    - nauka tworzenia twierdzy danych MINIO
    - konfiguracja bucketu
    - konfiguracja nowych kkluczy oraz dostęp do bucketów

### 💻 Stacje robocze (klienci)
- **Windows 11** – test logowania się do aplikacji, udział w SAMBIE oraz łączenie z VPN
---
