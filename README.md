# Public-Repository

Automatización de lavarropas a paleta con Microcontroladores.

INTRODUCCIÓN

	Este proyecto se realizó con el objetivo de fijar y afianzar los conocimientos sobre microprocesadores y microcontroladores, su  programación y simulación, obtener los conocimientos y habilidades necesarias para diseñar un sistema embebido; y para cumplimentar con las exigencias de examen final de la asignatura Procesadores II correspondiente a la carrera Ingeniería Electrónica con Orientación en Sistemas Digitales de Universidad Nacional de San Luis.
 	Se utilizó el lenguaje C, y sus diferentes métodos, para la  programación de un microcontrolador PIC, estudiado y utilizado durante el curso de la materia además de los microcontroladores ATMEL.
	En cuanto al proyecto, se baso en la idea de automatizar un lavarropas a paleta, es decir, se diseñará un circuito que permita generar retardos de varios minutos para controlar el motor; y manejar electro bombas, una electroválvula y un presostato de dos niveles para permitir el llenado y vaciado del lavarropas.

METODOLOGIA  DE  TRABAJO:

La metodología utilizada para llevar a cabo el proyecto fue simplemente un microcontrolador PIC 16F877A al cual se le agregaron interfaces con transistores BJT 547 y resistores para poder excitar un LED, un Speaker, una pantalla LCD LM016, y Relés para conectar el motor, electro bomba, electroválvulas y el presostato, a la línea de 220V (ca) y así aislar las tierras de los circuitos de baja y alta tensión. 
En cuanto a las entradas y salidas; se colocaron 2 pulsadores conectados con resistencias de pull-up por el cual se ingresan los datos para elegir los modos de lavado (modo_select); y para comenzar la secuencia del mismo (enter). Por el LCD se muestran los modos que se irán eligiendo antes de presionar la tecla “enter” y la acción que realiza el sistema en cada instante durante el lavado. También fue conectado un speaker que emite pitidos luego que se termino la secuencia de lavado y un LED rojo que indica que la secuencia de lavado ha comenzado, es decir, cuando la tecla “enter” ha sido presionada luego de elegir el modo de lavado con la tecla “modo_select” y se apaga luego de terminar con la secuencia de lavado.
El circuito se simuló en Proteus 7.5 y el código en lenguaje C se depuró en PIC-C Compiler.

CONCLUSIONES:

Una vez finalizado el trabajo, se valoró mucho la técnica de diseño “divide y conquistarás”, ya que facilitó bastante la realización del proyecto. Esta manera de abordar un problema, facilita también inmensamente la detección de errores.
	La realización de este trabajo, permitió la integración de los conocimientos adquiridos en la materia además de mostrar que, junto con los temas vistos en la materia “Interfaces”, se abren las puertas para poder abordar nuestros propios proyectos, esto se debe a que conocemos el lenguaje, el software, el conexionado del circuito, etc. De manera particular, considero muy útil la realización de este informe y la lectura en ingles de textos, ya que será de mucha importancia en nuestra carrera a futuro.
