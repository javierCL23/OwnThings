import time
import threading
from pynput.keyboard import Listener, KeyCode, Controller as KeyboardController
from pynput.mouse import Controller as MouseController, Button

# Tecla para iniciar/detener el programa
INICIAR = None

# Variables de configuración
pulsando = False
modo = None
clics_por_segundo = None
tecla_pulsar = None
boton_raton = None

# Controladores de ratón y teclado
raton = MouseController()
teclado = KeyboardController()

def elegir_velocidad():
    global clics_por_segundo
    while True:
        try:
            clics_por_segundo = float(input("Introduce el número de clics/pulsaciones por segundo: "))
            if clics_por_segundo > 0:
                break
        except ValueError:
            pass
        print("Por favor, introduce un número válido mayor que 0")

def elegir_modo():
    global modo
    while modo not in ["r", "k"]:
        modo = input("Elige el modo (raton:R/teclado:K): ").strip().lower()
    if modo == "r":
        elegir_boton_raton()
    if modo == "k":
        elegir_tecla()
    
    elegir_velocidad()

def elegir_boton_raton():
    global boton_raton
    eleccion = ""
    while eleccion not in ["d","i"]:
        eleccion = input("Elige el botón del ratón (izq:I/der:D): ").strip().lower()
    if eleccion == "d":
        boton_raton = Button.right
    if eleccion == "i":
        boton_raton = Button.left

def elegir_tecla():
    global tecla_pulsar
    tecla_pulsar = input("Introduce la tecla a pulsar: ").strip().lower()[0]


def elegir_boton_activacion():
    global INICIAR
    tecla = input("Elige tecla de trigger: ").lower()[0]
    INICIAR = KeyCode(char = tecla)
    print("TECLA TRIGGER:",tecla)

def autoclicker():
    global pulsando
    while True:
        if pulsando:
            raton.click(boton_raton, 1)
        time.sleep(1 / clics_por_segundo)

def autopresionador():
    global pulsando
    while True:
        if pulsando:
            teclado.tap(tecla_pulsar)
        time.sleep(1 / clics_por_segundo)

def empezar_evento(tecla):
    global pulsando
    if tecla == INICIAR:
        pulsando = not pulsando


# Configuración inicial
elegir_modo()
elegir_boton_activacion()

if modo == "r":
    hilo = threading.Thread(target=autoclicker)
if modo == "k":
    hilo = threading.Thread(target=autopresionador)

hilo.start()

# Escuchar la tecla de activación/desactivación
with Listener(on_press=empezar_evento) as listener:
    listener.join()
