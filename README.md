При запуске клиента и сервера необходимо ввести в текстовые поля адрес, порт и имя для файла(либо оставить по умолчанию), а затем нажать кнопку Apply.
Оба приложения подсчитывают кол-во отправленных и полученных файлов, а также кол-во ошибок.
Для генерации dto структур используется класс dtogenerator. Размер массива генерируется в диапазоне [0; 1000], а размер map в диапазоне [1; 15].
На стороне сервера парсинг полученного файла выполняется в отдельном потоке.
Для отображения отладочной информации необходимо в .pro файле раскомментировать CONFIG+=DEBUG_LOG и собрать оба приложения.
Примеры графических интерфейсов приложений и xml файлов можно посмотреть в папке Example
