# Ansible w homelabie

Ciągła automatyzacja jest jednym z kluczowych elementów nowoczesnych systemów informatycznych. W moim homelabie wykorzystałem **Ansible** do zarządzania infrastrukturą, automatyzacji deployu aplikacji oraz konfiguracji usług.

## Czym jest Ansible
- Narzędzie do automatyzacji administracji serwerami z wykorzystaniem SSH.  
- Pozwala na instalację oprogramowania, konfigurację systemów oraz wdrażanie aplikacji w sposób deklaratywny.  
- Działa bez agentów po stronie hostów i korzysta z plików YAML, co zwiększa czytelność i powtarzalność procesów.  

## Zastosowanie w homelabie

### 1. Automatyzacja Docker
- Tworzenie i uruchamianie testowych kontenerów Docker za pomocą `docker-compose.yml`.  
- Możliwość łatwego dodawania nowych kontenerów poprzez aktualizację `group_vars`.  
- Zapewnia powtarzalność i spójność środowiska.

### 2. Administracja Nginx
- Automatyczne dodawanie nowych stron statycznych i aplikacji do serwera Nginx.  
- Dynamiczne generowanie konfiguracji reverse proxy z wykorzystaniem szablonów Jinja.  
- Sprawdzanie dostępności wszystkich publikowanych URLi po wdrożeniu.

### 3. Automatyzacja monitoringu Prometheus
- Aktualizacja pliku konfiguracyjnego `prometheus.yml` i dodawanie nowych endpointów.  
- Restart kontenerów Prometheus i Grafana w celu zastosowania zmian.  
- Automatyzacja zarządzania monitoringiem w całym środowisku.

## Architektura
- **Kontroler Ansible**: lokalny serwer zarządzający wszystkimi playbookami.  
- **Hosty zdalne**: maszyny wirtualne lub kontenery odpowiedzialne za uruchomione usługi i monitoring.  
- Takie podejście pokazuje **świadomość architektury rozproszonej** i separacji ról w systemie.
