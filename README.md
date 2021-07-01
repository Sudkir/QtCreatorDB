#  Приложение для создания SQL скриптов
## Задача:
### Подключить PostgreSQL к проекту на Qt. Далее необходимо написать небольшое приложение, генерирующее скрипты БД в файлы:

+ Создать интерфейс для описания свойств БД (название, логин, пароль).
Должен генерировать файл с SQL скриптом создания БД;

+ Создать экран для создания таблиц в указанной БД, экран должен генерировать файл с SQL скриптами создания таблиц;

+ Создать такой интерфейс и наборы скриптов, которые позволят создавать связи между таблицами БД (внешние ключи);

## Для запуска приложения:
### Поместите файлы из папки dll в корневую папку с приложением, где находиться сам .exe

### Заменить данные в файле database.cpp на нужные

![image](https://user-images.githubusercontent.com/55054000/123833603-344b0280-d90f-11eb-8d0c-293463fa9ca8.png)

## Вход в приложение
Окно для заполнения данных о пользователе

![image](https://user-images.githubusercontent.com/55054000/123650418-40fa2880-d833-11eb-9129-7c899c19c79d.png)

Представление этих данных в БД

![image](https://user-images.githubusercontent.com/55054000/123651325-0a70dd80-d834-11eb-9d0a-25a73b87acdc.png)

## Основное рабочее пространство

### Общий вид окна
![image](https://user-images.githubusercontent.com/55054000/123650843-a3532900-d833-11eb-9609-e3dfdd9893a2.png)

Представления данных в БД

![image](https://user-images.githubusercontent.com/55054000/123651562-3f7d3000-d834-11eb-9583-f6006b3ee34a.png)

### Добавление новой Базы данных 

![image](https://user-images.githubusercontent.com/55054000/123651745-69ceed80-d834-11eb-97d0-59321f9b1110.png)

 После нажатия кнопки вызов окна путь сохранения скрипта 
 
 ![image](https://user-images.githubusercontent.com/55054000/123652023-9edb4000-d834-11eb-8f29-d2bd7a92dce7.png)

 ###  Добавление таблицы  конкретную БД
 
 ![image](https://user-images.githubusercontent.com/55054000/123652329-e1048180-d834-11eb-9790-fdb5610e5ac4.png)

после нажатия кнопки открывается следующее диалоговое окно

![image](https://user-images.githubusercontent.com/55054000/123652538-0f825c80-d835-11eb-9cc6-ce7a4c1c4107.png)

### Добавление внешних Ключей Между таблицами

![image](https://user-images.githubusercontent.com/55054000/123652693-317bdf00-d835-11eb-8876-45a3c6a2628e.png)

## Примеры самих SQL запросов созданных в системе

![image](https://user-images.githubusercontent.com/55054000/123653303-b109ae00-d835-11eb-8010-674a23c3eba3.png)


![image](https://user-images.githubusercontent.com/55054000/123652903-5d976000-d835-11eb-81c5-fb9d8fd04d04.png)

![image](https://user-images.githubusercontent.com/55054000/123652953-68ea8b80-d835-11eb-910d-70b11eedd145.png)

![image](https://user-images.githubusercontent.com/55054000/123653244-a51dec00-d835-11eb-8e67-83bdaaacf106.png)




