

$(function() 
{
$(document).ready( function()
{
   //var TXT_URL = 'https://www.mozilla.org/media/MPL/2.0/index.815ca599c9df.txt';
   var TXT_URL = "datos.txt";

    $.ajax
    (
    	{
        	url : TXT_URL,
			dataType: "text",
			success : function (data) 
			{
            	 $(".text").html("<<tr><th>FECHA</th><th>HORA</th><th>TEMPERATURA 1</th><th>TEMPERATURA 2</th><th>TEMPERATURA 3</th><th>HUMEDAD</th></tr>"+data);
			}
		}
	);
   });
});

