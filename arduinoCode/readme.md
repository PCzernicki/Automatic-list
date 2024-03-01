![Opis zdjęcia](20240301_203639.jpg)

### Schemat działania:

- moduł został uruchomiony
- ustawiony jest na nim stan inicjalizacyjny - initialState();
- prorgram działa w pętli, co sekunde sprawdza tagDetected(), czyli czy pojawiła się w zasięgu działania czytnika nowa karta, jeżeli się pojawiłą odczytuje jej UID jeżeli taki UID istnieje istnieje
- jeżeli karta jest nowa oraz UID istnieje uruchamiany jest beeper na 1000ms oraz na lcd wyświetla się "Authorizing..." przez 1000ms
- kod UID odczytany z karty zostaje wysłany na port szeregowy - sendDataToServer();
- aplikacja JAVA odbiera dane z portu szeregowego przetwarza je i zwraca Stringa spowrotem na port szeregowy
- Zwracany z JAVY String to Imię Nazwisko ( albo Hello Kowalski, możesz wejsć ) albo Unauthorized
- Arduino odbiera bajty z portu szeregowego jeżeli istnieją (czeka na to 2000ms)
- jeżeli po tym czasie nie ma żadnych bajtów w porcie wyświetlane jest na LCD info NO_MESSAGE_RECEIVED
- jeżeli jakieś bajty są, przetwarzane są one na Stringa i wyświetlane na LCD
- Jeżeli String != "Unauthorized" to zapala się LED ZIELONY na 5000ms.
