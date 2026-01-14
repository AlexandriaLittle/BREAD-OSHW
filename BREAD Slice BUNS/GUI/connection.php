<?php
$host = 'localhost'; //Replace these 4 variables with your database charcteristics
$username = 'root'; //'testing' for Rasp Pi
$password = ''; //'testing' for Rasp Pi
$database = 'testdb';

$connection = mysqli_connect($host, $username, $password, $database);

if (!$connection) {
    die('Connection error: ' . mysqli_connect_error());
}
?>