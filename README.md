# Название проекта
Лабораторная работа по решению задачи коммивояжёра. Проект позволяет ввести все данные удобным способом, показывает полное решение задачи методом [ветвей и границ](https://ru.wikipedia.org/wiki/Задача_коммивояжёра#cite_ref-3). Проект может нарисовать введённый граф и полученное решение с использованием OpenGL.

## Содержание
- [Технологии](#технологии)
- [Использование](#использование)
- [Тестирование](#тестирование)
- [Deploy и CI/CD](#deploy-и-ci/cd)
- [Contributing](#contributing)
- [To do](#to-do)
- [Команда проекта](#команда-проекта)

## Технологии
- [OpenGL](https://www.gatsbyjs.com/)
- [GLFW](https://www.glfw.org)
- [GLEW](https://glew.sourceforge.net)
- [gltext](https://github.com/vallentin/glText)

## Использование

### Требования
Для сборки проекта потребуется MSBuild, включённая в IDE Microsoft Visual Studio.

### Установка зависимостей
Собрать и запустить проект можно после установки вышеуказанных технологий, для этого можно использовать [vcpkg](https://github.com/microsoft/vcpkg)
```sh
$ vcpkg install glfw3:x64-windows-static
$ vcpkg install glfw3:x64-windows
$ vcpkg install glbinding:x64-windows-static
$ vcpkg install glbinding:x64-windows
$ vcpkg integrate install
```
Также потребуется библиотека-файл [gltext](https://github.com/vallentin/glText), она уже включена в проект.

### Создание билда
Чтобы выполнить сборку, выполните команду: 
```sh
msbuild.exe Travelling_Merchant.vcxproj
```

## Тестирование
Было произведено ручное тестирование. На этапе тестирования существенных недостатков выявлено не было.


## Команда проекта
Оставьте пользователям контакты и инструкции, как связаться с командой разработки.

- [Буковский Денис](https://t.me/TypicalGeek) — Студент группы РИС-23-3Б ПНИПУ.