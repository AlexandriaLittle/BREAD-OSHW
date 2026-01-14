<?php
include_once('connection.php');

if (isset($_GET['id'])) {
    $id = $_GET['id'];

    // Sanitize the ID
    $id = mysqli_real_escape_string($connection, $id);

    // Delete query
    $query = "DELETE FROM buns_table WHERE ID = '$id'";

    if (mysqli_query($connection, $query)) {
        // Redirect to the original page after deletion
        header("Location: index.php");
        exit();
    } else {
        echo "Error: " . mysqli_error($connection);
    }

    // Close the connection
    mysqli_close($connection);
} else {
    echo "Error: ID parameter is missing.";
}
?>