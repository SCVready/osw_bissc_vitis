
// 00110101 10111010 00100010 11001100

// Input value:           110101101110100010001011
// Input polinomio:                        1000011
// Resultado esperado:                      001100


//#########################################################################################

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

/****************************************************************************
* Function : generates the CRC sum from a given data set (pstrDataSetIn)  
*			 and CRC polynomial (pstrCRCPolyIn).  
*****************************************************************************/
char *pstrCRCGEN (char *pstrDataSetIn, char *pstrCRCPolyIn)
{
	int i,j;
	char        	*pstrDataSet = strdup(pstrDataSetIn),
					*pstrCRCPoly = strdup(pstrCRCPolyIn);
	unsigned short	usDatLen = strlen(pstrDataSet),
		            usCRCPolyLen = strlen(pstrCRCPoly),
	    	        usCRCLen = usCRCPolyLen-1;
	char        	*pstrCRC = malloc(usCRCLen);
	char        	cExOr = '0';

	pstrDataSet  = strrev(pstrDataSet);
	pstrCRCPoly = strrev(pstrCRCPoly);
  
  
	// Initialize pstrCRC with '0' 
	for (i = usCRCLen-1; i >= 0; i--)
    	pstrCRC[i] = '0';					
  
	// Calculate pstrCRC
	for (i = usDatLen-1; i >= 0; i--)
	{
    	switch (pstrDataSet[i])
    	{
    		case '0':
        		if (pstrCRC[usCRCLen-1] == '0')
        			cExOr = '0';
            	else
        	  		cExOr = '1';
    	    	break;
      
    		case '1':
        		if (pstrCRC[usCRCLen-1] == '1')
        		   	cExOr = '0';
        	    else
        	      	cExOr = '1';
    	    	break;
      
    		default:
    			exit (1);
    	}			
    
    	// 
		for (j = usCRCLen-1; j > 0; j--)					
		{
			if (pstrCRCPoly[j] == '1')
			{
        		if (pstrCRC[j-1] == cExOr) 
        			pstrCRC[j] = '0';
        		else
        			pstrCRC[j] = '1';
			}
			else
        		pstrCRC[j] = pstrCRC[j-1];
		}			
		pstrCRC[0] = cExOr;  // Bit 0
	}
    free(pstrDataSet);
    free(pstrCRCPoly);
	return (pstrCRC);
}
/*
// Main function (prints calculated CRC)
char *main(int argc, char *argv[])
{
	int  i = 0;
	char *pstrCRCWert = NULL;

	if (argc < 2)
	{
		printf("Call: CRCGen <data> <CRC-Poly>\n");
		printf("        <data> binary data, the crc-code should be created for\n");
	    //printf("        <CRC-Poly> binary Polynomial, used to create the CRC\n");
	    return (0);
	}
	else
	{
	    pstrCRCWert = pstrCRCGEN (argv[1], argv[2]);
	    printf ("\n\n");
	    printf ("data   %s\n", argv[1]);
	    printf ("CRC Polynomial  %s\n", argv[2]);
	    printf ("\nergibt CRC  ");
	    for (i = strlen(argv[2])-2; i >= 0; i--)
	      printf ("%c", pstrCRCWert[i]);
	    printf ("\n\n\n");
	}
	return (pstrCRCWert);
}
*/
//#########################################################################################