<?php
include_once('connection.php');

// Retrieve the form data
$item = $_POST['item'];
$quantity = $_POST['quantity'];
$description = $_POST['description'];
$barcode = $_POST['barcode'];

// Insert the new entry into the database
$query = "INSERT INTO buns_table (Item, Quantity, Description, Barcode) VALUES ('$item', $quantity, '$description', '$barcode')";
$result = mysqli_query($connection, $query);

if($result) {
    echo 'New entry added successfully';
} else {
    echo 'Error: ' . mysqli_error($connection);
}
?>
