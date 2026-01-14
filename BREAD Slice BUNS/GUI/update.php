<?php
include_once('connection.php');

if (isset($_POST['id']) && isset($_POST['item']) && isset($_POST['quantity']) && isset($_POST['description']) && isset($_POST['barcode'])) {
    $id = $_POST['id'];
    $item = $_POST['item'];
    $quantity = $_POST['quantity'];
    $description = $_POST['description'];
    $barcode = $_POST['barcode'];

    // Sanitize input to prevent SQL injection
    $id = mysqli_real_escape_string($connection, $id);
    $item = mysqli_real_escape_string($connection, $item);
    $quantity = mysqli_real_escape_string($connection, $quantity);
    $description = mysqli_real_escape_string($connection, $description);
    $barcode = mysqli_real_escape_string($connection, $barcode);

    // Update query
    $query = "UPDATE buns_table SET Item = '$item', Quantity = '$quantity', Description = '$description', Barcode = '$barcode' WHERE id = '$id'";

    if (mysqli_query($connection, $query)) {
        echo "Success";
    } else {
        echo "Error: " . mysqli_error($connection);
    }

    mysqli_close($connection);
} else {
    echo "Error: Missing required parameters.";
}
?>
