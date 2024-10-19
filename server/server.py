from flask import Flask, request, jsonify
import json
from datetime import datetime

app = Flask(__name__)

# Ruta para recibir los datos de los sensores y loguearlos en un archivo
@app.route('/api/data', methods=['POST'])
def receive_data():
    # Verifica si los datos están en formato JSON
    if request.is_json:
        sensor_data = request.get_json()
        log_data(sensor_data)
        return jsonify({"message": "Datos recibidos correctamente"}), 200
    else:
        return jsonify({"error": "Formato no válido, se espera JSON"}), 400

# Función para loguear los datos en un archivo
def log_data(data):
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')  # Obtener la hora actual
    with open("sensor_data.log", "a") as log_file:  # Abrir el archivo en modo "append"
        log_entry = f"{timestamp} - {json.dumps(data)}\n"  # Formato de la entrada de log
        log_file.write(log_entry)  # Escribir la entrada en el archivo
        print(f"Datos logueados: {log_entry}")  # Imprimir en la consola para referencia

# Ruta para mostrar el contenido del log
@app.route('/api/data', methods=['GET'])
def show_data():
    try:
        with open("sensor_data.log", "r") as log_file:
            log_content = log_file.read()
        return f"<pre>{log_content}</pre>", 200
    except FileNotFoundError:
        return jsonify({"message": "No se ha encontrado el archivo de log"}), 404

if __name__ == '__main__':
    # Ejecuta el servidor en el puerto 5000
    app.run(host='0.0.0.0', port=5000, debug=True)
