<?php 
session_start(); 
//don't allow user to directly come to this page without logging in.
if($_SESSION['login']==false)
	header('Location: index.php');
	
//if they are going to the checkout then redirect them appropriately
if(isset($_POST['purchase']))
{
  			header('Location: orderprocessing.php');
}
    	 
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">

<head>
	<title>Hi Fidelity Audio - Shopping Cart</title>
	<meta name="Description" content="Brads speaker shop" />
	<meta name="Keywords" content="css layout" />
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"/>
	<link rel="stylesheet" href="template.css" type="text/css" />
	<script type="text/javascript" src="validate.js"> </script>
</head>
<body>
	
	

<div id="wrapper">
    <div id="header">
          <?php require("header.php");?>
    </div>

    <div id="nav">
    	<?php require("navbar.php");?>
    </div>

    <div id="main">
     
    <h3> Search for Products </h3>
    Please enter your search criteria below and click search.<br/><br/>
  
   
 	<form method=post > 
		<div>
		<strong>Brand</strong><br/>
			
		<input type="checkbox" name="brandTannoy" value="Tannoy" /> Tannoy
		<input type="checkbox" name="brandB&W" value="Bowers and Wilkins" /> Bowers and Wilkins<br /><br/>
		
		<strong>Speaker Configuration </strong> <br/>
		<input type="checkbox" name="configuration2" value="2 Channel" /> 2 Channel
		<input type="checkbox" name="configuration5" value="5.1 Channel" /> 5.1 Channel<br /><br/>
		
		<strong>Product/Model Name (case insensitive contains search) </strong> <br/>
		Model: <input type="text" name="model" /><br /><br/>
		
		<input type="submit" value="Search" name="search" />
		
		<h3> Search Results </h3>
   		<?php require "productsearch.php" ?>
   </form>		 	 
   
	</div>
	    
    <div id="right"
     
    <h3> Your Shopping Cart </h3>
    
    <?php 
    	
    	/*handle delete button*/
    	if(isset($_POST['submit']))
  		{
  			$itemname = $_POST['h1'];
  			//update the price
  			$_SESSION['totalcost']-=$_SESSION['itemprice'][$itemname];
  			
  			//if there is more than one qty just decrement
  			if($_SESSION['itemqty'][$itemname]>1)
  				$_SESSION['itemqty'][$itemname]--;
  			//only one in the cart so just remove it
  			else
  			{
  				unset($_SESSION['itemqty'][$itemname]);
  				unset($_SESSION['itemprice'][$itemname]);
  				unset($_SESSION['itemname'][$itemname]);
  				$_SESSION['qty']=0;
  			}
  		
  		}
  		
  	
    	//check if the shopping cartis empty 
    	if(count($_SESSION['itemname'])==0)
    		echo "Shopping cart is empty";
    	//its not so display everything in the cart
    	else
    	{
    	 	echo "<br/><br/>";
  		 	echo "<table border='1'>";
  		 	echo "<tr><th>Name</th><th>Quantity</th><th>Price (AUD)</th></tr>";
 		 	
 		 	foreach($_SESSION['itemname'] as $key=>$value)
			{

			echo "<tr><td>".$_SESSION['itemname'][$key]."</td>";
			echo "<td> ".$_SESSION['itemqty'][$key]."</td>";
			echo "<td>".$_SESSION['itemprice'][$key]."</td><td>";
			echo "<form id=f1 method=post name=\"f1\"><input type=\"submit\" name=\"submit\" value =\"delete\">";
			echo "<input type=hidden name=h1 value=\"".$key."\"></td></tr>";
				echo "</form>";
			}
      		echo "<td> </td>  <td> Total Cost</td> <td>".$_SESSION['totalcost']."</td>";
      		echo "</table>";
      		
      		echo "<form method=post>";
    		echo "<input type=submit value=\"Proceed to payment\" name=purchase />";
    		echo "</form>";
    
      	}
 
    ?>
    </div>
	
     <div id="footer">
    	<?php require("footer.php"); ?>
    </div>
    
</div>
    
</body>
</html>