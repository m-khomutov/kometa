# Эмулятор вида из окна на море и программа просмотра

**Сборка**

`git clone https://github.com/m-khomutov/kometa.git`  
`cd kometa/`  
`mkdir build`  
  
Возможные варианты сборки:  
* с использованием toolkit-a Qt  
`.qmake`  
`make all`  
  
* с использованием cmake  
`cd build/`  
`cmake ..`  
`make all`  

**Установка с использованием toolkit-a Qt**  
  
* Файл запуска эмулятора  
  >build/simulator/app/simulator  
* Файл запуска программы просмотра  
  >build/viewer/app/viewer  
  
**Установка с использованием cmake**  
* Эмулятор  
  >build/simulator/simulator  
* Программа просмотра  
  >build/viewer/viewer  

**Запуск**
  
* Эмулятор  
 `simulator -s ../../../simulator/shaders/ -d 40 -w 800x600 -t ../../../simulator/textures`  
  
* Программа просмотрa  
 `viewer -u http://127.0.0.1:2232/`  

**Параметры запуска (выводятся опцией -h)**  

* Эмулятор  
  
```$ simulator -h  
Вывод опций программы  
Запуск: ./simulator[-h] [-s] [-t] [-p] [-g] [-q] [-d] [-w]  
  
Эмулятор устройства  
   
обязательные аргументы:  
 	  -s	каталог с шейдерами  
 	  -t	каталог с текстурами  
Опциональные аргументы:  
 	  -p	порт прослушки (def. 2232)  
 	  -g	размерность пространства [2D|3D] (def. 3D)  
 	  -w	размеры окна (def. 800x600)  
 	  -q	качество сжатия % (def. 80)  
 	  -d	длительность кадра мс (def. 40)  
 	  -h	вывод параметров запуска  
  ```
* Программа просмотрa  
  
```$ viewer -h  
Вывод опций программы  
Запуск: ./viewer[-h] [-u] [-w] [-v]  
   
программа просмотра  
  
обязательные аргументы:  
 	  -u	url эмулятора  
Опциональные аргументы:  
 	  -w	размеры окна (def. 800x600)  
 	  -v	вывод оценки задержки (def. false)  
 	  -h	вывод параметров запуска  
  ```
