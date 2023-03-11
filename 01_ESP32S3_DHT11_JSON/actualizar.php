<?php

$datos = array("temperature" => 0, "humidity" => 0); // Valores iniciales

// Obtener los datos de temperatura y humedad del ESP32-S3
$temp = $_GET['temp'];
$hum = $_GET['hum'];

// Actualizar los valores en el archivo "datos.json"
$datos["temperature"] = $temp;
$datos["humidity"] = $hum;
file_put_contents('datos.json', json_encode($datos));

?>
