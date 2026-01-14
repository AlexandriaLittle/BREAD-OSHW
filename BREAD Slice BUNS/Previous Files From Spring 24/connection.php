<?php
$host = 'localhost'; //Replace these 4 variables with your database charcteristics
$username = 'testing';
$password = 'testing';
$database = 'testdb';

$connection = mysqli_connect($host, $username, $password, $database);

if (!$connection) {
    die('Connection error: ' . mysqli_connect_error());
}
?>