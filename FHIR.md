# Achitektura IT szpitala
Architektura IT szpitala należy do jednych z najbardziej złożonych środowisk informatycznych, często przewyższając pod tym względem systemy spotykane w dużych przedsiębiorstwach. Obejmuje ona nie tylko rozwiązania do monitorowania wydajności infrastruktury (serwery, sieci, urządzenia medyczne), lecz także wyspecjalizowane systemy do gromadzenia, przetwarzania i zarządzania danymi medycznymi pacjentów.
W środowisku szpitalnym funkcjonuje wiele systemów o różnych zadaniach, takich jak HIS (Hospital Information System), RIS (Radiology Information System), LIS (Laboratory Information System), PACS czy systemy apteczne. Rynek systemów medycznych jest bardzo rozdrobniony i obejmuje wielu dostawców, co powoduje konieczność zapewnienia sprawnej i bezpiecznej wymiany danych pomiędzy nimi. Kluczowym wyzwaniem jest tu interoperacyjność, czyli zdolność systemów do wzajemnej komunikacji w sposób jednoznaczny i zgodny z przyjętymi standardami.
W odpowiedzi na te potrzeby powstała organizacja HL7 (Health Level Seven), której celem jest definiowanie standardów komunikacji oraz formatów danych umożliwiających wymianę informacji medycznych pomiędzy heterogenicznymi systemami informatycznymi.

## HL7 v2
HL7 v2 jest najpowszechniej stosowanym standardem wymiany danych medycznych na świecie. Opiera się on na komunikatach tekstowych przesyłanych pomiędzy systemami, najczęściej w modelu point-to-point. Komunikaty HL7 v2 składają się z segmentów (np. MSH, PID, OBR, OBX), które z kolei dzielą się na pola i komponenty oddzielone specjalnymi separatorami znakowymi.
Standard ten charakteryzuje się dużą elastycznością oraz tolerancją na lokalne rozszerzenia, co przyczyniło się do jego szerokiej adopcji, ale jednocześnie powoduje problemy z jednoznacznością implementacji. W praktyce oznacza to, że różni dostawcy mogą interpretować te same komunikaty w nieco odmienny sposób, co często wymaga stosowania silników integracyjnych (np. Mirth Connect) do mapowania i transformacji danych.

## HL7 FHIR
HL7 FHIR (Fast Healthcare Interoperability Resources) jest nowoczesnym standardem opracowanym jako odpowiedź na ograniczenia HL7 v2 i v3. FHIR łączy doświadczenia poprzednich wersji HL7 z podejściem znanym z technologii webowych i REST-owych interfejsów API.
Podstawową jednostką danych w FHIR są tzw. zasoby (resources), takie jak Patient, Observation, ServiceRequest czy Encounter. Każdy zasób ma ściśle zdefiniowaną strukturę i może być reprezentowany w formacie JSON lub XML. Komunikacja z serwerem FHIR odbywa się zazwyczaj poprzez protokół HTTP z użyciem standardowych metod REST (GET, POST, PUT, DELETE).

# Integracja systemowa w praktyce
Znajomość działania systemów w jaki sposób je integorwac jest kluczową umiejętnością inżynierów systemów medycznych. W tym celu zostało utworzone laboratorium mające na celu przyswojenia tej wiedzy.
Wykorzystano do tego 3 kontenery LXC:
- HAPI FHIR Server
- Mirth Connect
- RIS/PACS

## Hapi FHIR Server 
HAPI FHIR to open-source’owy framework w Javie służący do tworzenia i obsługi serwerów oraz klientów zgodnych ze standardem HL7 FHIR. Udostępnia gotowy serwer referencyjny (HAPI FHIR JPA Server), który pozwala szybko przechowywać i udostępniać zasoby FHIR, takie jak Patient, Observation czy ServiceRequest. 
Framework wspiera REST API, walidację zasobów, wyszukiwanie oraz wersjonowanie danych zgodnie ze specyfikacją FHIR. Dzięki modularnej budowie HAPI FHIR łatwo integruje się z innymi systemami medycznymi oraz narzędziami integracyjnymi.

## Mirth Connect
To silnik integracyjny (integration engine) wykorzystywany głównie w ochronie zdrowia do wymiany danych między systemami medycznymi. Najczęściej obsługuje standard HL7 v2, ale potrafi też pracować z FHIR, XML, JSON, CSV czy komunikacją REST/HTTP. 
Umożliwia budowanie kanałów integracyjnych z filtrami, transformerami i connectorami, w których można mapować, walidować i modyfikować dane.
W laboratorium Mirth został użyty do integracji między serwerem FHIR, serwerem PsuedoRIS.
### Generowanie zleceń 
Mirth odpytuje FHR czy posiada aktywne zlecenia radiologiczne. Na ich podstawie tworzy nowy wiersz w bazie danych dla zlecenia oraz jeśli pacjent nie istnieje w bazie tworzy nowego pacjenta o podanym id. Następnie tworzony jest plik .wml do worklisty PACS-a.
Po wynkonaniu wszystkich powyższych kroków zmieniany jest status w FHIS na `draft`.
### Generowanie opisów
Po wykonaiu opisu pseudoris wysyła do mirth ramkę HL7 ORU. Po otrzymaniu jej mirth konwertuje ją na odpowiedni endpoint do FHIR. 
W celu trzymania opisu w kilku miejscach, mirth genenruje plik `.pdf` opisowy, który po konwersji na base64 wgrywany jest do badania radiologicznego na PACS-ie.
Na koniec zmieniany jest status zlecenia w FHIR na `complete`.
