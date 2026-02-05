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

# Nginx

## Cel
**Nginx** służy jako:
- serwera HTTP,
- reverse proxy,
- elementu infrastruktury DevOps,
- fundamentu pod obsługę TLS, Dockera oraz dalszą naukę orkiestracji (Kubernetes).

##  Strony statyczne
Utworzono **trzy statyczne strony internetowe**:
- `site1`
- `site2`
- `site3`

Każda strona:
- posiada osobny katalog w `/var/www/html/`,
- jest serwowana bezpośrednio przez Nginx,
- wykorzystuje mechanizm `location` oraz `alias`,
- dostępna jest poprzez HTTPS.

## Aplikacje backendowe (Python + Flask)

Zostały stworzone aplikacje wykorzystujące framework pythonow Flask:

| Aplikacja  | Port kontenera | Ścieżka w Nginx |
|-----------|----------------|-----------------|
| simpleapp | 5000           | `/simpleapp`    |
| innaapp   | 5500           | `/innaapp`      |
| testapi   | 5550           |  `/testapi`     |

Cechy:
- każda aplikacja działa w osobnym kontenerze Docker,
- kontenery nasłuchują wyłącznie na `127.0.0.1`,
- dostęp z zewnątrz realizowany jest wyłącznie przez Nginx (reverse proxy),
- routing odbywa się na podstawie ścieżki URL (path-based routing).


## Aplikacja frontendowa (React)

Stworzono aplikację webową typu SPA (**Single Page Application**) w technologii **React**:
- aplikacja budowana jest w trybie produkcyjnym (`npm run build`),
- pliki statyczne serwowane są przez Nginx,
- aplikacja dostępna jest pod ścieżką `/cv`,
- poprawnie obsługuje routing frontendowy (React Router),
- poprawnie ładowane są zasoby statyczne (`/static/js`, `/static/css`).



## Reverse Proxy (Nginx)

Nginx pełni rolę **centralnego reverse proxy**, odpowiadając za:
- terminację TLS (HTTPS),
- routing ruchu do odpowiednich aplikacji,
- izolację aplikacji backendowych od bezpośredniego dostępu z sieci,
- jednolity punkt wejścia dla wszystkich usług.

