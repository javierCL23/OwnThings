import os
import pandas as pd
import re

# Carpeta donde están los archivos .txt
carpeta = "ficheros"
archivo_salida = "datos.xlsx"

# Lista para almacenar los datos de cada archivo
datos_acumulados = []

# Recorrer todos los archivos .txt en la carpeta
for archivo in os.listdir(carpeta):
    if archivo.endswith(".txt"):
        ruta_archivo = os.path.join(carpeta, archivo)
        
        # Leer archivo con codificación latin-1
        with open(ruta_archivo, "r", encoding="latin-1") as f:
            lineas = f.readlines()

        datos = {}  # Diccionario para almacenar los datos del archivo

        for linea in lineas:
            if "=" in linea:
                clave, valor = linea.strip().split("=", 1)
                clave, valor = clave.strip(), valor.strip()
                
                # Reemplazar puntos en números por comas, excepto en el nombre del archivo
                if re.match(r"^-?\d+(\.\d+)?$", valor):  # Detecta números con punto decimal
                    valor = valor.replace(".", ",")

                # Convertir los campos de fecha
                if clave in ["Date", "Date(UT)"]:
                    try:
                        valor = pd.to_datetime(valor, format="%d%m%y").strftime("%Y-%m-%d")
                    except Exception:
                        pass  # Si falla, deja el valor original

                datos[clave] = valor

        # Agregar el nombre del archivo con su extensión como la primera columna
        datos["Imported_File"] = archivo

        datos_acumulados.append(datos)

# Crear DataFrame asegurando que todos los campos estén presentes
df = pd.DataFrame(datos_acumulados).fillna("")

# Reordenar las columnas para que "Imported_File" sea la primera
columnas_ordenadas = ["Imported_File"] + [col for col in df.columns if col != "Imported_File"]
df = df[columnas_ordenadas]

# Guardar en Excel
df.to_excel(archivo_salida, index=False)

print(f"Proceso completado. Datos guardados en {archivo_salida}")