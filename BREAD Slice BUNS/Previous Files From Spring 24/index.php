/*
Open Source Hardware Enterprise at Michigan Technological University
BREAD: BUNS

This is the HTML code for the website. Update the table to meet your needs.

*/


<?php
	include_once('connection.php');
	$query="SELECT * FROM count";
	$result=mysqli_query($connection, $query);

	if(!$result){
		die('Query faild: ' . mysqli_error($connection));
	}
?>

<!DOCTYPE html>
<html>
<head>
	<title>
		Bunz //Tabe title
	</title>
</head>
<body>

	<table align="center" border="1px" style="width:600px; line-height:40px;">
		<tr>
			<th colspan="4"><h2>Data</h2></th> //4 colums
		</tr>
		<tr>
			<th>Name</th>						//4 tiles for the columns
			<th>Count</th>
			<th>Edit</th>
			<th>Delete</th>
		</tr>
	<?php
		while($rows=mysqli_fetch_assoc($result)){
	?>
			<tr>
				<td><?php echo $rows['Name']; ?></td>
				<td><?php echo $rows['Number']; ?></td>
				<td><a href="#" class="btn btn-primary">Edit</a></td>
				<td><a href="#" class="btn btn-danger">Delete</a></td>
			</tr>
	<?php
		}
	?>
	</table>

</body>
</html>
