# Wirtualizacja klaysyczna
Proxmox umożliwia wirtualizację klasycznych środowisk. W tym projekcie wykorzystano jedno środowisko stojące na ubuntu 24.03. 
Wykorzystywana jest jako host dla aplikacji do monitoringu działań i wydajności aplikacji oraz wykorzystanych środowisk lub administracji kontenerów.
Sama wirtualka nazywa się `monitoring`, a podgląd do niej jest udostępniony za pomocą SSH lub z poziomu GUI Proxmoxa. 

## Portainer - aplikacja GUI do administracji kontenerów
Administracja Dockera bywa czasochłonna. Tymbardziej w przypadku posiadania ich na kilku środowiskach. Wykorzystanie Portainera pozwala administrować wszystko związane z Dockerem. 
Posiada bardzo intuicyjne GUI pozwalające w szybki i łatwy sposób zarządzać i sprawdz stan faktyczny aplikacji i nie tylko. 
Dzięki tej aplikacji mogłem przyswoić wiedzę z zakresu działania Dockera, a dokładniej:
- obrazy
- sieć
- volumeny
- kontenery

Podsumowując aplikacja ta pozwoliła zwiększyć produktywność oraz wiedzę w zakresie działania Dockera i konteneryzacji.

## Zabbix - kontrolowanie wybranych sytuacji 
`Zabbix` to aplikacja opensourcowa do pełnego monitoringu funkcjonowania środowisk znajdujących się w homelabie.
Zabbix do działania wykorzystuje agentów, umożliwiający pobieranie danych z lokalnego środwiska, ale też i z zewnątrz. 
Aplikacja ma duży wachlarz możliwości, ale w tym projekcie uwaga została skupiona na funkcjonalności alertowania.
Zabbix za pomocą odpowiednich `externalscriptow` wywoluje monitorowanie dla pewnych scenariuszy. Są one `0-1`, czy metoda `działa-nie działa`. W przypadku tego projektu monitorowane jest:
- działanie mirth
- działanie PACS-a
- działania wykonywanie Backup-u do MinioS3
  
Każde nieprawidłowe działanie włącza odpowiedni Trigger, który powoduje wysłanie na mail administartorski. 

## Prometheus - kolekcjonowanie metryk funkcjonowania oraz wydajności
Ważną umiejętnością sysadmina jest analiza funkcjonowania orz wydajności systemów i aplikacji. Monitorowanie w każdym z osobna jest małoefektywne, dlatego ważne jest wykorzystywanie centralizacji. 
Prometheus, to aplikacja do centralnego magazynowania metryk, tj. wartości odzwierciedlających wydajności. 
Dane te są zbierane w czasie rzeczywistym. Wykorzystywani są agenci, którzy monitorują:
- nginx
- docker
- serwer orthanc
- minioS3
  
Wszyscy monitorowani agenci są wypisani w pliku `.yml`
```
TODO:
```

## Grafana - profesjonalna wizualizacja danych w czasie rzeczywistym
Dane zebrane z metryk potrzeba prawidłowo zaprezentować w czasie rzeczywistym.
`Grafana` pozwala na tworzenie profesjonalnych wizualizacji w rózńym stylu. 

W projekcie zostały stworzone wykresy dla większości podanych powyżej danych i zostały zaprezentowane poniżej:
```
TODO
```
## Grafana Loki - analiza logów
Ważnym elementem analizy błedów jest czytanie logów. Loki to aplikacja do profesjonalnej analizy logów z podziałem na aplikację pochodzącą w czasie rzeczywistym. 
Host Loki można w bardzo prosty sposób podpiąc do Grafany, gdzie można stworzyć odpowiedni Dashboard.
W przypadku tego projektu stworzono dwa proste dashboardy dla dockera oraz nginx. 
```
TODO:
```
