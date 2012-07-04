<?php session_start();


/*handle adding to the cart*/
if (isset($_POST['addtocart']))
{
	
  	if($_SESSION['item']==$_POST['h1'])
	{
  		$_SESSION['qty'] = $_SESSION['qty'] + 1;
	}
	else
	{
  		$_SESSION['item'] = $_POST['h1'];
  		$_SESSION['price']= $_POST['h2'];
  		$_SESSION['qty'] =1;
	}

 	$_SESSION['itemname'][$_SESSION['item']] = $_SESSION['item'];
 	$_SESSION['itemqty'][$_SESSION['item']] = $_SESSION['qty'];
 	$_SESSION['itemprice'][$_SESSION['item']] = $_SESSION['price'];

	//update total cost
	$_SESSION['totalcost']+=$_POST['h2'];
}
		
if(isset($_POST['search']))
{
	//read all products from file into array
	$products = file("products.txt");
	$searchindex=array(count($products));
	$numproducts=count($products);

	
	//loop through each product and remove products that dont match search filters that have been set
	foreach($products as $line_num => $product)
	{
		//brand|model|speaker config|price|url
		
		$productinfo=explode('|',$product);
		$removeproduct=false;
		
		
		//echo "looking at ".$product." on line number ".$line_num." <br/>";
		//show by default
		$searchindex[$line_num]=true;
		
		//filter based upon brand
		//if 1 brand was chosen then filtering will be required. If none or both are selected no filtering will occur based upon brand
		if( !empty($_POST['brandTannoy']) ||!empty($_POST['brandB&W']))
		{

			//if tannoy is deselected
			if(empty($_POST['brandTannoy'])) 	
			{
				if($productinfo[0]=="Tannoy")
						$removeproduct=true;
			}
			//if b&w is deselected then remove it
			if(empty($_POST['brandB&W']))
			{
				if($productinfo[0]=="Bowers and Wilkins")
						$removeproduct=true;
			}
			
		}
		
		//filter based upon speaker amount
		//if 1 amount was chosen then filtering will be required. If none or both are selected no filtering will occur based upon brand
		if( !empty($_POST['configuration2']) ||!empty($_POST['configuration5']))
		{

			//if 2 is deselected
			if(empty($_POST['configuration2'])) 	
			{
				if($productinfo[2]=="2")
						$removeproduct=true;
			}
			//if b&w is deselected then remove it
			if(empty($_POST['configuration5']))
			{
				if($productinfo[2]=="5.1")
						$removeproduct=true;
			}
			
		}
		
		//filter based upon model entered
		if(!empty($_POST['model']))
		{
			if(!strpos(strtoupper($productinfo[1]),strtoupper($_POST['model'])))
				$removeproduct=true;
		}
		
		if($removeproduct)
		{
			$searchindex[$line_num]=false;
			$numproducts--;
		}
	}
		
		//Display search results
		if($numproducts>0)
		{
			echo "<table border='1'>";
  			echo "<tr><th>Brand</th><th>Model</th><th>Details</th><th>Price (AUD)</th><th>Add to Cart</th></tr>";
  		
			for($i=0;$i<count($searchindex);$i++)
			{
				if($searchindex[$i]==true)
				{
					$product=$products[$i];
					$productinfo=explode('|',$product);
					//generate table
					echo "<tr><td>$productinfo[0]</td>"; //brand
					echo "<td>$productinfo[1]</td>";//model
					echo "<td><a href='$productinfo[4]'><input type='button' value='Product Details'/></a></td>";
					echo "<td>$productinfo[3]</td>";//price
					
					//add the add to cart form for this product
					echo "<td><form method=post>";
					echo "<input type=submit name=addtocart value=Add to cart/>";
					echo "<input type=hidden name=h1 value=\"".$productinfo[1]."\"/>";
					echo "<input type=hidden name=h2 value=\"".$productinfo[3]."\"/>";
					echo "</form> </td>";
			

				}
			}
			echo "</table>";
		}
		else
			echo "No products matching your selecting criteria";
	
}
	


	


?>