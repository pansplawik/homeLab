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
Aktualnie posiada dwa główne kanały.
### Generowanie zleceń 
Mirth odpytuje FHR czy posiada aktywne zlecenia radiologiczne. Na ich podstawie tworzy nowy wiersz w bazie danych dla zlecenia oraz jeśli pacjent nie istnieje w bazie tworzy nowego pacjenta o podanym id. Następnie tworzony jest plik .wml do worklisty PACS-a.
Po wynkonaniu wszystkich powyższych kroków zmieniany jest status w FHIS na `draft`.
### Generowanie opisów
Po wykonaiu opisu pseudoris wysyła do mirth ramkę HL7 ORU. Po otrzymaniu jej mirth konwertuje ją na odpowiedni endpoint do FHIR. 
W celu trzymania opisu w kilku miejscach, mirth genenruje plik `.pdf` opisowy, który po konwersji na base64 wgrywany jest do badania radiologicznego na PACS-ie.
Na koniec zmieniany jest status zlecenia w FHIR na `complete`.

## PseudoRIS
RIS, czyli `Radiology Information System` to kluczowe miejsce do gromadzenia danych o zleceniach badań radiologicznych. 
Na podstawie danych znajdujących się w tym systemie gnenerowane są badania, gromadzone opisy oraz generowane raporty pacjentów. 
W celach laboratoryjnych został stworzony prototyp systemu RIS. 
Posiada prostą bazę danych zawierająca trzy tabele: `zlecenia`,`pacjenci`,`opisy`.
Zapisuje najważniejsze dane nt. zlecenia takie jak: idzlecenia, kod procedury, nazwa badania, notatka kliniczna, data zlecenia.
Synchronizacja RIS-PACS odbywa sie za pomocą id zlecenia pochodząca z FHIR: `ID zlecenia FHIR = ID zlecenia PseudoRIS = Numer dostepu PACS`
OPis jest możliwy tylko w przypadku synchronizacji RIS-PACS. 
Wszystkie dane o pacjencie oraz zleceniu dostępne są w module opisowym. 
Po Wykonaniu opisu generowana jest ramka HL7ORU i wysyłana do Mirth, a sam opis zapisany jest w osobnej bazie i podpięty do zlecenia RIS. Na ten moment nieprzewidywana jest możliwość poprawki opisu.
W przyszłości planowana jest priorytetyzowanie zleceń na podstawie tagi priority z zlecenia FHIR.
W momencie pisania tej dokumentacji aplikacja jest prototypem wersji RIS-owej i służy tlyko do podglądu mechanizmów działania systemu radiologicznego oraz pracy w nim.

## Orthanc PACS
Orthanc to lekki, open-source serwer DICOM/PACS, służący do przechowywania, zarządzania i udostępniania badań obrazowych.
Udostępnia REST API, wtyczki i integracje, dzięki czemu łatwo łączy się z innymi systemami.
Ze względu na brak modułu zleceniowego oraz opisowego mocno synchronizuje się z systemem PseudoRIS.
Służy do przeglądania oraz gromadzenia badań.

# Typy komunikatów wykorzystywanych w laboratorium
## HL7 ORU
HL7 ORU message result posiada kompletne dane na temat wyniku oraz opisu badania diagnostycznego. Generowany jest w momnecie zakonczenia opisu w PseudoRIS i wysyłany jest do Mirth w celu dalszego mapowania. 
Przykładowa ramka:
```
MSH|^~\&|RIS|RIS_HOSPITAL|PACS|PACS_HOSPITAL|20260128211957||ORU^R01|219153|P|2.5.1
PID|1||219177^^^HOSPITAL^MR||Nowak^Jan||19850412|M|||ul. Zdrowa 10^^Warszawa^^00-001^PL||600700800
ORC|RE|219196|||||20260129
OBR|1|219196||77477000^CT głowy^SNOMED|||20260129|||||||||||||||||||||||||
OBX|1|TX|RESULT^Opis badania^L||TK głowy bez kontrastu\.br\Brak cech krwawienia\.br\Układ komorowy symetryczny||||||F
```
Jak widać komunikat podzielony jest na następujące segmenty:
- `MSH` - Nagłówek wiadomości określający typ komunikatu (ORU^R01), system nadawcy i odbiorcy, datę wysłania oraz identyfikator komunikatu.
- `PID` – Segment pacjenta zawierający identyfikator, imię i nazwisko, datę urodzenia, płeć oraz dane adresowe i kontaktowe.
- `ORC` – Segment zlecenia, który identyfikuje konkretne skierowanie/badanie i w Twoim projekcie mapuje się bezpośrednio na ServiceRequest w FHIR.
- `OBR` – Segment szczegółów badania opisujący wykonane badanie obrazowe (np. CT głowy) wraz z kodem medycznym i datą realizacji.
- `OBX` – Segment wyniku zawierający opis badania, czyli właściwy raport lekarza, który trafia do Observation w FHIR.
## FHIR - Utworzenie pacjenta
- `POST /Patient`
- Przykład:
```
curl -X POST \
  http://localhost:8080/hapi-fhir-jpaserver/fhir/Patient \
  -H "Content-Type: application/fhir+json" \
  -H "Accept: application/fhir+json" \
  -d '{
    "resourceType": "Patient",
    "identifier": [{
      "system": "http://hospital.example.org/mrn",
      "value": "MRN-0002"
    }],
    "name": [{
      "use": "official",
      "family": "Nowak",
      "given": ["Jan"],
      "prefix": ["Pan"]
    }],
    "gender": "male",
    "birthDate": "1985-04-12",
    "telecom": [{
      "system": "phone",
      "value": "600700800"
    }],
    "address": [{
      "line": ["ul. Zdrowa 10"],
      "city": "Warszawa",
      "postalCode": "00-001",
      "country": "PL"
    }]
  }'
```
- Cel: stworzenie pacjenta, do którego później przypinane są zlecenia i wyniki.

## FHIR Utworzenie skierowania (ServiceRequest – badanie obrazowe)
- `POST /ServiceRequest`
- Przykład:
```
curl -X POST \
  http://localhost:8080/hapi-fhir-jpaserver/fhir/ServiceRequest \
  -H "Content-Type: application/fhir+json" \
  -H "Accept: application/fhir+json" \
  -d '{
    "resourceType": "ServiceRequest",
    "status": "active",
    "intent": "order",
    "priority": "routine",
    "category": [{
      "coding": [{
        "system": "http://terminology.hl7.org/CodeSystem/service-request-category",
        "code": "imaging",
        "display": "Imaging"
      }]
    }],
    "code": {
      "coding": [{
        "system": "http://snomed.info/sct",
        "code": "77477000",
        "display": "CT of head"
      }],
      "text": "CT głowy"
    },
    "subject": {
      "reference": "Patient/219177"
    },
    "authoredOn": "2026-01-29",
    "reasonCode": [{
      "text": "Bóle głowy, podejrzenie zmian śródczaszkowych"
    }],
    "note": [{
      "text": "Badanie TK głowy bez kontrastu"
    }]
  }'
```
- Cel: tworzenie nowwego zlecenia
  
## FHIR Pobranie aktywnych skierowań obrazowych
- `GET /ServiceRequest?category=imaging&status=active`
- Przykład:
```
curl -X GET \
  "http://localhost:8080/hapi-fhir-jpaserver/fhir/ServiceRequest?category=imaging&status=active&_count=1" \
  -H "Accept: application/fhir+json"
```
- Cel: uzyskanie aktywnych zleceń w celu utworzenia zleceń w systemie RIS

## FHIR Dodanie opisu
- `POST /Observation`
- Przykład:
```
curl -X POST \
  http://localhost:8080/hapi-fhir-jpaserver/fhir/Observation \
  -H "Content-Type: application/fhir+json" \
  -H "Accept: application/fhir+json" \
  -d '{
    "resourceType": "Observation",
    "status": "final",
    "category": [{
      "coding": [{
        "system": "http://terminology.hl7.org/CodeSystem/observation-category",
        "code": "imaging",
        "display": "Imaging"
      }]
    }],
    "code": {
      "coding": [{
        "system": "http://snomed.info/sct",
        "code": "363680008",
        "display": "Chest X-ray"
      }],
      "text": "RTG klatki piersiowej"
    },
    "subject": {
      "reference": "Patient/219177"
    },
    "basedOn": [{
      "reference": "ServiceRequest/219153"
    }],
    "effectiveDateTime": "2026-01-29T21:30:00Z",
    "valueString": "Brak zmian ogniskowych, sylwetka serca prawidłowa."
  }'
```

## FHIR Zmiana statusu ServiceRequest na completed
- `PUT /ServiceRequest/{id}`
- Przykład:
```
curl -X PUT \
  http://localhost:8080/hapi-fhir-jpaserver/fhir/ServiceRequest/219153 \
  -H "Content-Type: application/fhir+json" \
  -H "Accept: application/fhir+json" \
  -d '{
    "resourceType": "ServiceRequest",
    "id": "219153",
    "status": "completed"
  }'
```
