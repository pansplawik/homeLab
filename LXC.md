# Wykorzystanie LXC do systemu PACS oraz aplikacji do integracji

Proxmox posiada wbudowaną możliwość konteneryzacji pojedynczych aplikacji z wykorzystaniem technologii **LXC (Linux Containers)**. Rozwiązanie to umożliwia uruchamianie aplikacji w odizolowanych środowiskach, które współdzielą jądro systemu operacyjnego hosta, co znacząco zmniejsza narzut na zasoby w porównaniu do klasycznych maszyn wirtualnych. Kontenery LXC działają jak lekkie systemy operacyjne, zapewniając jednocześnie separację procesów, sieci oraz systemu plików.

Możliwość ta została wykorzystana przy tworzeniu:
- systemu PACS (**Orthanc**)
- aplikacji do integracji systemowej (**Mirth Connect**)
- serwera NGINX
- serwera FHIR

Zastosowanie LXC pozwoliło na uproszczenie wdrażania i zarządzania aplikacjami, a także na łatwiejsze wykonywanie kopii zapasowych oraz migracji usług pomiędzy hostami. Dodatkowo konteneryzacja zwiększa bezpieczeństwo poprzez izolację aplikacji oraz ograniczenie wpływu awarii jednego komponentu na pozostałe elementy systemu. Dzięki niewielkiemu zużyciu zasobów LXC stanowi efektywne rozwiązanie dla uruchamiania wyspecjalizowanych usług medycznych w środowisku szpitalnym.
