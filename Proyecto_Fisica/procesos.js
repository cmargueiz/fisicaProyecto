

$(function() 
{
$(document).ready( function()
{
   //var TXT_URL = 'https://www.mozilla.org/media/MPL/2.0/index.815ca599c9df.txt';
   var TXT_URL = "sensor1.txt";

    $.ajax
    (
    	{
        	url : TXT_URL,
			dataType: "text",
			success : function (data) 
			{
            	 $(".text").html("<<tr><td>Sensor 1</td></tr>"+data);
			}
		}
	);
   });
});

