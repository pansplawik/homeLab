# Modele wirtualizacji w środowiskach IT

## On-Premises
On-premises polega na utrzymywaniu całej infrastruktury sprzętowej, wirtualizacyjnej i aplikacyjnej we własnej lokalizacji. Administratorzy mają pełną kontrolę nad sprzętem, siecią i dostępnością usług. Minusem jest konieczność samodzielnego dbania o aktualizacje, kopie zapasowe i bezpieczeństwo.

## Chmura (Cloud)
Rozwiązania chmurowe wykorzystują infrastrukturę udostępnioną i utrzymywaną przez zewnętrznego dostawcę. Użytkownik zarządza jedynie systemami operacyjnymi i aplikacjami, a odpowiedzialność za sprzęt i dostępność spoczywa na dostawcy. Model chmurowy zapewnia elastyczność skalowania zasobów i szybkie wdrożenie nowych usług.

## Hybryda
Model hybrydowy łączy zalety wirtualizacji lokalnej i chmurowej. Krytyczne systemy działają lokalnie, co daje pełną kontrolę, natomiast usługi mniej wrażliwe lub wymagające wysokiej dostępności mogą być hostowane w chmurze. Takie podejście zwiększa elastyczność, bezpieczeństwo i pozwala na optymalne wykorzystanie zasobów infrastruktury.

# Wykorzystywane rozwiązanie wirtualizacji

W tym projekcie zastosowano **hybrydowe podejście do wirtualizacji**, łączące klasyczne maszyny wirtualne (VM) z kontenerami LXC.  
Na platformie **Proxmox VE** uruchamiane są zarówno pełne maszyny wirtualne z systemem Ubuntu Server, jak i lekkie kontenery LXC dla pojedynczych aplikacji medycznych i usług infrastrukturalnych.  
Podejście hybrydowe pozwala na pełną kontrolę nad krytycznymi usługami, efektywne wykorzystanie zasobów sprzętowych oraz łatwą izolację i skalowanie aplikacji w środowisku laboratoryjnym.

## Wykorzystane aplikacje

### MinioS3 – backup
MinioS3 jest lokalnym serwerem kompatybilnym z API S3, który służy do przechowywania kopii zapasowych. W projekcie wykorzystano go do gromadzenia backupów baz danych, obrazów medycznych oraz konfiguracji aplikacji, zgodnie z zasadą 3-2-1. Dzięki MinioS3 możliwe jest testowanie procedur odtwarzania systemu w bezpiecznym i elastycznym środowisku.

### WikiJS – portfolio
WikiJS został wykorzystany jako centralne narzędzie do dokumentowania całego projektu. Pozwala tworzyć strukturalną, wersjonowaną dokumentację w formacie Markdown, obejmującą opis infrastruktury, konfiguracje usług, procedury backupu i bezpieczeństwa. Dzięki WikiJS możliwe jest łatwe udostępnianie i aktualizowanie wiedzy o systemie, a także przygotowanie przejrzystego i profesjonalnego portfolio prezentującego kompetencje w zakresie DevOps i administracji systemami.

# Wirtualny zewnętrzny storage - NextCLoud
Zgodnie z zasadą 3-2-1 jedna z kopii backupu powinna znajdować się w dwóch fizycznych lokalizacjach. 
Wykorzystano rozwiązanie chmurowe `NextCloud`, do gromadzenia backupu wszszytkich plików znajdujących się na VM oraz LXC.
Aby zintegrować udostępnianie folder z backupem wykorzystano `davfs2` do montowania WebDAV jako osobny dysk. 
W celu skompletowania rozwiązania dodano odpowiedni skrypt w `crontab`, aby regularnie wykonywać backup raz w dziennie.
