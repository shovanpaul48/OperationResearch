
/*Given Table 
	D1	 D2 	..... Dn 	Supply
O1 
O2
.
.
.
On
Demand	
*/




#include <stdio.h>
#include<stdlib.h>

int FindMinimumCost(int rows, int columns, int **table){
    int i,j,f =1, small_cost, small_cost_column, small_cost_row;
    int minimum_cost =0 ,count = 1;

    while (f == 1 )	{
	f = -1;
	small_cost = 2147483647;
    printf("\nTraverse:  %d ------------------------------ \n",count);
	for (i = 1; i<= rows -1; i ++){
		for (j = 1; j <= columns -1 ; j++){
            printf("%d   ",table[i][j]);
			if (small_cost > table[i][j] && table[i][j] != -1) { // *remember that  >= may change the minimum cost  but both are true 
				small_cost = table[i][j];
				small_cost_column = j;
				small_cost_row = i ;
				f = 1 ;
			}
		}
        printf("\n");
	}
    if (f == -1)
        return minimum_cost;
	minimum_cost = ChangeSupplyDemand(small_cost,small_cost_column, small_cost_row,minimum_cost, rows,columns, table);
    count ++;
    printf("\nMCost: %d %d %d %d\n",minimum_cost, small_cost,small_cost_row,small_cost_column);
	}
    return minimum_cost;
}
 
int ChangeSupplyDemand(int small_cost,int small_cost_column,int small_cost_row, int minimum_cost, int rows,int columns,int **table){
	int a, b,i,j;
	// Check small cost supply is minor or demand is minor 

	a = table[small_cost_row][columns];   // supply
	b = table[rows][small_cost_column] ;  // demand
	if (a > b ) {   // IF supply is greater than demand then change supply value 
        j = small_cost*b;
		minimum_cost =  minimum_cost + j ;
		table[small_cost_row][columns] = a - b ; 
		for (i =1 ; i <= rows ; i++)// making demand coloumn to -1 to not select next time
			table[i][small_cost_column] = -1; 

		table[rows][small_cost_column] = 0;
	}

	else if (b > a){  // if demand is greater than supply then change demand value
        j = small_cost*a;
		minimum_cost =  minimum_cost + j ;
		table[rows][small_cost_column]  = b - a ;
		for (i =1 ; i <= columns ; i++) // making supply row to -1 to not select next time
			table[small_cost_row][i] = -1;
			
		table[small_cost_row][columns] = 0;
	}
	
	else if (b == a){  // if demand is greater than supply then change demand value
		minimum_cost =  minimum_cost + small_cost*a ;
		table[rows][small_cost_column]  = 0;
		table[small_cost_row][columns]  = 0;
		for (i =1 ; i <= columns ; i++) // making supply row to -1 to not select next time
			table[small_cost_row][i] = -1;
		for (i =1 ; i <= rows ; i++) // making demand column to -1 to not select next time
			table[i][small_cost_column] = -1;
	}
    printf("Now table is \n ");
    for( i = 1 ; i<= rows; i++){
        for(j = 1; j <= columns ; j++){
            printf("%d      ",table[i][j]);
        }
        printf("\n");
    }
    printf("\nMCost %d   j: %d  s:%d   a:%d  b:%d \n",minimum_cost,j, small_cost, j,a,b);

	return minimum_cost;
}

int main() {
    int rows ,columns, i, j,a,b,c,d; // Insert rows and column  number manually 
    // int *r, *c;
	int **table, **table2; // table2 is use if dummmy row or column needed
    int supply_sum = 0 , demand_sum = 0;
    int minimum_cost = 0;
    int count = 1;


    printf("Enter No of rows : ");
    scanf("%d",&rows);
    printf("Enter No of columns: ");
    scanf("%d",&columns);
    // rows = r;
    // columns = c;

    table = malloc(sizeof(int *) * rows);

    // printf("Row and Column value must be entered manually before comiling")
    printf("!!! Minimum cost output may be differ from given answer \nIf so, then change on line 30: if small_cost > table[i][j] then convert to small_cost >= table[i][j] or vice versa !!!! \n");
    

    printf("Remember at last column enter supply value !!! \n");
    for (i = 1;i <= rows; i++) {
        table[i] = malloc(sizeof(int)*columns) ; 
    	if (i == rows){
			printf("In this row enter only demand values !!! \n");
			demand_sum = 0;
		}	
        for (j = 1;j <= columns; j++) {
        	if (i== rows && j == columns) {
        		printf("This is the last corner, So its value is 0 \n");
        		table[i][j] = 0;
			}
			else {
				printf("Enter value for table[%d][%d]:", i, j);
         		scanf("%d", &table[i][j]);
			}
         	demand_sum  = demand_sum + table[i][j] ;
         	if (j == columns)
         		supply_sum  = supply_sum + table[i][j] ;
         	
    	}
    }

    for( i = 1 ; i<= rows; i++){
        for(j = 1; j <= columns ; j++){
            printf("%d      ",table[i][j]);
        }
        printf("\n");
    }


/*	
   	Now Lest Cost Apply method  
    Step 1:  Find the minimum value from cost matrix (  D1 - Dn)
    												 O1
    											      | 
    											     (On      )
    											     
    Step 2 :  check for smaller value between supply and demand
    Step 3 : if supply is smaller then then multiply minimum cost and supply and add to  minimum cost 
	       	step3_1 : make demand = demand - supply
	       	step3_2: make whole row values  -1 
    Step 4 : if demand is smaller then then multiply minimum cost and deman and add to  minimum cost 
	    	step3_1 : make supply = supply -demand
	   		step3_2: make whole column values  -1 
	
	step 5 :repeat step 1 to 4 until all values gets -1
    											     
*/  	
	
    if (supply_sum == demand_sum ){
    	printf("Table is balanced \n");
        minimum_cost = FindMinimumCost(rows, columns, table);
	}
	
	else if (supply_sum < demand_sum ) {   // if supply is less then add dummy row in table2
		printf("Supply and demand not same adding dummy row \n");
		c = demand_sum - supply_sum ;
        // step1 : copy data from table1 to table 2 and then add dummy data
        table2 = malloc(sizeof(int *) * (rows + 1) );
        for (i =1 ; i<= rows-1; i++){
            table2[i] = malloc(sizeof(int) * columns);
            for ( j = 1; j<=columns;j++)
                table2[i][j] =  table[i][j];
        }
        table2[rows] = malloc(sizeof(int) * columns); // adding dummy row 
        for (i = 1 ; i<= columns-1; i++)
            table2[rows][i] = 0 ;
        table2[rows][columns] = c ;

        table2[rows+1] = malloc(sizeof(int) * columns); //  adding demand row
        for (i = 1 ; i<= columns; i++)
            table2[rows+1][i] = table[rows][i] ;

        minimum_cost = FindMinimumCost(rows+1, columns, table2);
    }
	
	else if (supply_sum > demand_sum ) { // if demand is less then add dummy column 
		c =  supply_sum - demand_sum  ;
        // step1 : copy data from table1 to table 2 and then add dummy data 
        table2 = malloc(sizeof(int *) * rows );
        for (i =1 ; i<= rows ; i++){
            table2[i] = malloc(sizeof(int) * (columns + 1)); // adding dummy column
            for ( j = 1; j<=columns;j++)
                table2[i][j] =  table[i][j];
            
            if (i == rows)
                 table2[i][columns] = c ;             // adding dummy demand value 
            else
                table2[i][columns] = 0 ;              // adding dummy data to column
    
            table2[i][columns+1] = table[i][columns]; //adding supply value

        }
        minimum_cost = FindMinimumCost(rows, columns +1, table2);     
	}
				    
	
	printf("\n Minimum cost is : %d", minimum_cost);


    return 0;
}


