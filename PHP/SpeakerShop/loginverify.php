<?php 
$log=$_POST['log'];
$password=$_POST['password'];

if(isset($_POST['login']))
{
	
	if(empty($log))
	{
		$error="Login cannot be empty. Please specify your email";
	}

	
	if(empty($password)) 
	{ 
		$error= "No password entered. Try again";
	}
	
	//Check the users.txt file and see if this person is a valid member.
	if(empty($error))
	{
		$fp=fopen("users.txt","r");
		while(!feof($fp))
		{
			$line=explode('&',fgets($fp));
			//get the name from the line read in used for password
			$name=explode('=',$line[0]);			
			//get the email from the line read in used for login id
			$email=explode('=',$line[5]);
		
			//verify login detials
		
			if($log==trim($email[1]) && $password==trim($name[1]))
			{
				//get the rest of the information . this will be looked up later in purchase confir
				$lastname=explode('=',$line[1]);
				$age=explode('=',$line[2]);
				$address=explode('=',$line[3]);
				$city=explode('=',$line[4]);
			
				$_SESSION['login']=true;
				$_SESSION['email']=trim($email[1]);
				$_SESSION['firstname']=trim($name[1]);
				$_SESSION['lastname']=trim($lastname[1]);
				$_SESSION['age']=trim($age[1]);
				$_SESSION['address']=trim($address[1]);
				$_SESSION['city']=trim($city[1]);
				
				echo "<h3> Continue to shop by clicking on Products and purchase by going to Shopping Cart ! </h3>";
				//header('Location: products.php');
				return;
			}
			else
			{
				//No they aren't so don't let them in.
				$login=false;
				$error= "Login failed for ".$log;
			
			}
		
		}
	}
	echo $error;
	return;
		
}
?>