#  Portfolio/ HomeLab - symulacja architektury IT Szpitala
## Analityczne podejście

Informatyczny system szpitalny charakteryzuje się wysokim poziomem złożoności. Składa się on z wielu współpracujących ze sobą komponentów, takich jak wirtualizowane lub skonteneryzowane aplikacje medyczne i szpitalne, systemy monitorujące pracę całej infrastruktury oraz urządzenia i mechanizmy odpowiedzialne za bezpieczeństwo.

Ze względu na krytyczny charakter przetwarzanych danych oraz konieczność zapewnienia wysokiej dostępności usług, projektowanie takiego systemu wymaga analitycznego podejścia. Każdy element infrastruktury musi być oceniany pod kątem wydajności, niezawodności, bezpieczeństwa oraz możliwości skalowania.

Szczególną uwagę zwrócono na logiczny podział systemu na warstwy funkcjonalne, co ułatwia zarządzanie, diagnostykę oraz dalszy rozwój infrastruktury. Zastosowanie wirtualizacji i konteneryzacji pozwala na izolację usług, ograniczenie wpływu awarii pojedynczego komponentu oraz efektywniejsze wykorzystanie zasobów sprzętowych.

Dodatkowo uwzględniono mechanizmy monitoringu i logowania, które umożliwiają bieżącą analizę stanu systemu oraz szybką reakcję na potencjalne nieprawidłowości. Całość rozwiązania została zaprojektowana z myślą o spełnieniu wymagań systemów medycznych, takich jak ciągłość działania, integralność danych oraz zgodność z obowiązującymi standardami bezpieczeństwa.
## Ogólna specyfikacja techniczna


W celu stworzenia kompletnego i niskobudżetowego projektu wykorzystano sprawdzone, otwartoźródłowe rozwiązania dostępne na rynku. Kluczowym elementem infrastruktury jest hypervisor **KVM** w postaci platformy **Proxmox VE**. Jest to system do wirtualizacji, który umożliwia jednoczesne zarządzanie maszynami wirtualnymi (VM) oraz kontenerami aplikacyjnymi (LXC) z poziomu jednego środowiska.

Jednym z głównych powodów wyboru Proxmox VE jest natywna obsługa **konteneryzacji LXC**. Rozwiązanie to sprawdza się idealnie w przypadku uruchamiania pojedynczych aplikacji lub lekkich usług, gdzie nie ma potrzeby tworzenia pełnych maszyn wirtualnych. Kontenery charakteryzują się mniejszym narzutem na zasoby oraz szybszym czasem uruchamiania. Takie podejście zostało zastosowane m.in. przy budowie systemu **PACS** oraz integracji pomiędzy innymi systemami. [Zostało to opisane tutaj.](/LXC.md)

Proxmox VE został również wykorzystany do klasycznej wirtualizacji systemów Linux, takich jak **Ubuntu Server**. Jedną z kluczowych maszyn wirtualnych jest VM odpowiedzialna za uruchamianie skonteneryzowanych aplikacji służących do **monitorowania działania całej infrastruktury**. Szczegóły tego rozwiązania zostały opisane w dedykowanym rozdziale. [Opisane w tym rozdziale.](/VM.md)

Współczesne systemy IT coraz częściej opierają się na rozwiązaniach chmurowych, odchodząc od utrzymywania całej infrastruktury w lokalnych centrach danych. W prezentowanym projekcie zastosowano **model hybrydowy**, łączący infrastrukturę lokalną z zasobami zewnętrznymi. W tym celu wykorzystano serwer **VPS**, który pełni kilka istotnych funkcji.
Jedną z nich jest rola **repozytorium kopii zapasowych**, zgodnie z zasadą **3-2-1 backup**. Dodatkowo VPS został wykorzystany do zbierania i przetwarzania danych pochodzących z systemu monitorowania temperatury i wilgotności w mieszkaniu. Dane te są przesyłane z mikrokontrolerów (co stanowi jedno z moich hobby) z wykorzystaniem protokołu **MQTT**. [Więcej szczegółów znajduje się tutaj.](/VPS.md)
