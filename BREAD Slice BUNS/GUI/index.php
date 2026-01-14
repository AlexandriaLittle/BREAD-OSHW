<!--
Open Source Hardware Enterprise at Michigan Technological University
BREAD: BUNS

This is the HTML code for the website. Update the table to meet your needs.
-->


<?php
	include_once('connection.php');
	$query="SELECT * FROM buns_table";
	$result=mysqli_query($connection, $query);

	if(!$result){
		die('Query failed: ' .mysqli_error($connection));
	}
?>

<!DOCTYPE html>
<html>
<head>
	<title>Bunz</title>
	<meta charset="UTF-8">
	<link rel="stylesheet" type="text/css" href="styles.css">
</head>
<body>
	<div class="table-container">
	<table align="center" class="styled-table">
    	<thead>
        	<tr>
            	<th colspan="6">
                	<h2>Database</h2>
                	<button class="btn btn-add" onClick="openAddModal()">Add New Entry</button>
            	</th>
        	</tr>
        	<tr>
            	<th>Name</th>
            	<th>Quantity</th>
            	<th>Description</th>
            	<th>Barcode</th>
            	<th>Edit</th>
            	<th>Delete</th>
        	</tr>
    	</thead>
    	<tbody id="data-container">
        	<!-- Data rows will be inserted here by JavaScript -->
    	</tbody>
	</table>
	</div>

	<img src="OSHElogo.jpg" class="OSHE-logo">

</body>
</html>

	<!-- Modal for Editing -->
	<div id="editModal" class="modal">
		<div class="modal-content">
			<span class="close" onClick="closeModal()">&times;</span>
			<h2>Edit Item</h2>
			<form id="editForm">
				<input type="hidden" id="editId">
				<label for="itemName">Name:</label><br>
				<input type="text" id="itemName"><br><br>
				<label for="itemQuantity">Quantity:</label><br>
				<input type="number" id="itemQuantity"><br><br>
				<label for="itemDescription">Description:</label><br>
				<textarea id="itemDescription"></textarea><br><br>
				<label for="itemBarcode">Barcode:</label><br>
				<input type="text" id="itemBarcode"><br><br>
				<button type="button" onClick="saveChanges()">Save Changes</button>
			</form>
		</div>
	</div>

	<!-- Modal for Adding New Entry -->
	<div id="addModal" class="modal">
		<div class="modal-content">
			<span class="close" onClick="closeAddModal()">&times;</span>
			<h2>Add New Item</h2>
			<form id="addForm">
				<label for="newItemName">Name:</label><br>
				<input type="text" id="newItemName"><br><br>
				<label for="newItemQuantity">Quantity:</label><br>
				<input type="number" id="newItemQuantity"><br><br>
				<label for="newItemDescription">Description:</label><br>
				<textarea id="newItemDescription"></textarea><br><br>
				<label for="newItemBarcode">Barcode:</label><br>
				<input type="text" id="newItemBarcode"><br><br>
				<button type="button" onClick="saveNewEntry()">Save Entry</button>
			</form>
		</div>
	</div>

	<script>
		// Open Modal and Populate with Data
		function openModal(id, name, quantity, description, barcode) {
			document.getElementById('editId').value = id;
			document.getElementById('itemName').value = name;
			document.getElementById('itemQuantity').value = quantity;
			document.getElementById('itemDescription').value = description;
			document.getElementById('itemBarcode').value = barcode;
			document.getElementById('editModal').style.display = 'block';
		}

		// Close Modal
		function closeModal() {
			document.getElementById('editModal').style.display = 'none';
		}

		function saveChanges() {
    		let id = document.getElementById('editId').value;
    		let name = document.getElementById('itemName').value;
			let quantity = document.getElementById('itemQuantity').value;
			let description = document.getElementById('itemDescription').value;
			let barcode = document.getElementById('itemBarcode').value;

			// AJAX request to update.php
			let xhr = new XMLHttpRequest();
			xhr.open('POST', 'update.php', true);
			xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

			// Handle response
			xhr.onload = function() {
				if (xhr.status === 200) {
					alert('Data updated successfully');
					location.reload();  // Reload the page to reflect changes
				} else {
					alert('Error: Could not update data.');
				}
			};

			// Send data to update.php
			xhr.send(`id=${id}&item=${name}&quantity=${quantity}&description=${description}&barcode=${barcode}`);
		}

		function confirmDelete(id) {
    		if (confirm("Are you sure you want to delete this record?")) {
        		window.location.href = "delete.php?id=" + id;
    		}
		}

		// Open the "Add New Entry" Modal
		function openAddModal() {
        	document.getElementById('addModal').style.display = 'block';
    	}

    	// Close the "Add New Entry" Modal
    	function closeAddModal() {
        	document.getElementById('addModal').style.display = 'none';
    	}

    	// Function to save the new entry using AJAX
		function saveNewEntry() {
			let name = document.getElementById('newItemName').value;
			let quantity = document.getElementById('newItemQuantity').value;
			let description = document.getElementById('newItemDescription').value;
			let barcode = document.getElementById('newItemBarcode').value;

			// AJAX request to insert.php
			let xhr = new XMLHttpRequest();
			xhr.open('POST', 'insert.php', true);
			xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

			// Handle response
			xhr.onload = function() {
				if (xhr.status === 200) {
					alert('New entry added successfully');
					location.reload();  // Reload the page to reflect changes
				} else {
					alert('Error: Could not add entry.');
				}
			};

			// Send data to insert.php
			xhr.send(`item=${name}&quantity=${quantity}&description=${description}&barcode=${barcode}`);
		}

		// Hide the modal when the page loads
		window.onload = function() {
			document.getElementById('editModal').style.display = 'none';
			document.getElementById('addModal').style.display = 'none';
			updateTable();
		}

		function updateTable() {
    		let xhr = new XMLHttpRequest();
    		xhr.open("GET", "fetch_data.php", true);
    		xhr.onload = function() {
        		if (xhr.status === 200) {
            		let data = JSON.parse(xhr.responseText);
            		let tableContent = "";
            		data.forEach(row => {
                		tableContent += `
                    		<tr>
                        		<td>${row.Item}</td>
                        		<td>${row.Quantity}</td>
                        		<td>${row.Description}</td>
                        		<td>${row.Barcode}</td>
                        		<td>
                            		<button class="btn btn-primary" onClick="openModal(${row.ID}, '${row.Item}', ${row.Quantity}, '${row.Description}', '${row.Barcode}')">
                                		<i class="icon-edit"></i><span>Edit</span>
                            		</button>
                        		</td>
                        		<td>
                            		<button class="btn btn-danger" onClick="confirmDelete(${row.ID})">
                                		<i class="icon-delete"></i><span>Delete</span>
                            		</button>
                        		</td>
                    		</tr>`;
            		});
            		document.getElementById("data-container").innerHTML = tableContent;
        		}
    		};
    		xhr.send();
		}

		// Poll for updates every 5 seconds
		setInterval(updateTable, 5000);
	</script>
</body>
</html>