
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

int DoUntilFindMinimumCost(int rows,int columns,int **table,int *penalty_of_row,int *penalty_of_col,int minimum_cost){
    int i,j,a,b,max_row_penalty = -2147483647 , max_col_penalty = -2147483647 ;
    int f = 1,count=0;


    while (f == 1 )	{
        f = -1;
        max_row_penalty = -2147483647 ;
        max_col_penalty = -2147483647 ;
        printf("\nTraverse:  %d ------------------------------ \n",count);
        for (i = 1; i<= rows -1; i ++){
            for (j = 1; j <= columns -1 ; j++){
                printf("%d   ",table[i][j]);
                if (table[i][j] != -1) 
                    f = 1 ;
            }
            printf("\n");
        }
        if (f == -1)
            return minimum_cost;
        
        count++;
        FindPenalty(rows,columns,table,penalty_of_row,penalty_of_col );
        // Find MAximum penalty
        for (i = 1;i<=rows-1;i++)    // here ]]]]
            if (max_row_penalty < penalty_of_row[i]){
                max_row_penalty = penalty_of_row[i] ;
                a = i ;        // Storing maximum row penalty value
            }
        
        for (i = 1;i<=columns-1;i++)
            if (max_col_penalty < penalty_of_col[i]){
                max_col_penalty = penalty_of_col[i] ;
                b = i ;         // Storing maximum column penalty value
            }

        //
        if (max_row_penalty > max_col_penalty){  // if row is greater then solve row first
            printf("\nMCost: %d mcp:%d mrp:%d  >r\n",minimum_cost, max_col_penalty,max_row_penalty); 
            minimum_cost = FindMinimumInCell(rows,columns,table,a,-1,minimum_cost);
            penalty_of_row[a] = -1;  // after using this penalty we set it to -1
        }
        else{
            minimum_cost = FindMinimumInCell(rows,columns,table,-1,b,minimum_cost);
            printf("\nMCost: %d mcp:%d mrp:%d  >c\n",minimum_cost, max_col_penalty,max_row_penalty); 
            penalty_of_row[b] = -1;  // after using this penalty we set it to -1
        }
    }
    return minimum_cost;
}

int FindMinimumInCell(int rows,int columns,int **table, int r,int c, int minimum_cost){
    int i,j,min = 2147483647,a,b;
    int m_cost = 0;

    if (r != -1 && c==-1){ // row will be change 
        for (i=1;i<=columns-1;i++){
            if (table[r][i] < min  && table[r][i] != -1 ){
                min = table[r][i];
                a = i;        // storing row index
            }
        }
        minimum_cost = ChangeSupplyDemand(min,a,r,minimum_cost,rows,columns,table);
    }

    if (c != -1 && r ==-1){
        for(i=1;i<=rows-1;i++){
            if(table[i][c] < min  && table[i][c] != -1){
                min = table[i][c];
                b = i;           // storing column index;
            }
        }
        minimum_cost =  ChangeSupplyDemand(min,c,b,minimum_cost,rows,columns,table); 
    }
    printf("#==> mCost : %d ",minimum_cost);

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
		for (i =1 ; i <= rows-1 ; i++)// making demand coloumn to -1 to not select next time
			table[i][small_cost_column] = -1; 

		table[rows][small_cost_column] = 0;
	}

	else if (b > a){  // if demand is greater than supply then change demand value
        j = small_cost*a;
		minimum_cost =  minimum_cost + j ;
		table[rows][small_cost_column]  = b - a ;
		for (i =1 ; i <= columns-1 ; i++) // making supply row to -1 to not select next time
			table[small_cost_row][i] = -1;
			
		table[small_cost_row][columns] = 0;
	}
	
	else if (b == a){  // if demand is greater than supply then change demand value
		minimum_cost =  minimum_cost + small_cost*a ;
		table[rows][small_cost_column]  = 0;
		table[small_cost_row][columns]  = 0;
		for (i =1 ; i <= columns-1 ; i++) // making supply row to -1 to not select next time
			table[small_cost_row][i] = -1;
		for (i =1 ; i <= rows-1 ; i++)    // making demand column to -1 to not select next time
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


int FindPenalty(int rows,int columns,int **table,int *penalty_of_row,int *penalty_of_col){
    int i, j,a,b;
    // Speacially for VAM variabels
    int min ,min2;
    printf("In FindPenalty \n");
    for (i=1;i<=rows-1;i++){
        min =2147483647 ;
        min2= 2147483646;
        for (j=1; j<= columns-1;j++){
            if (table[i][j] < min && table[i][j] != -1 ){
                min = table[i][j];
                b = j ; 
            }
        }
        for (j=1; j<= columns-1;j++){
            if (table[i][j] >= min && table[i][j] <= min2 && b != j && table[i][j] != -1)
                min2 = table[i][j];
        }
        printf("(min2:%d   min:%d) ",min2,min);
        penalty_of_row[i] = (min2 - min);

        
    }
    
    printf("\n");
    for (i=1;i<=columns-1;i++){
        min =2147483647 ;
        min2= 2147483646;
        for (j=1; j<= rows-1;j++){
            if (table[j][i] < min && table[j][i] != -1){
                min = table[j][i];
                b = j;
            }
        }
        for (j=1; j<= rows-1;j++){
            if (table[j][i] >= min && table[j][i] <= min2 && b != j && table[j][i] != -1)
                min2 = table[j][i];
        }
        printf("(min2:%d   min:%d) ",min2,min);
        penalty_of_col[i] = (min2 - min);
        printf("%d  ",penalty_of_col[i]);
        
    }
    
    printf("\nPenalty of Row: ");
    for (i = 1;i<= rows-1;i++)
        printf("%d  ",penalty_of_row[i]);

    printf("\nPenalty of Column: ");
    for (i = 1;i<= columns-1;i++)
        printf("%d  ",penalty_of_col[i]);

    printf("\n");


}


int main() {
    int rows ,columns, i, j,a,b,c,d; // Insert rows and column  number manually 
    // int *r, *c;
	int **table, **table2; // table2 is use if dummmy row or column needed
    int supply_sum = 0 , demand_sum = 0;
    int minimum_cost = 0;
    int count = 1;
    
    int *penalty_of_row, *penalty_of_col, max_row_penalty = -2147483647 , max_col_penalty = -2147483647 ; 


    printf("Enter No of rows : ");
    scanf("%d",&rows);
    printf("Enter No of columns: ");
    scanf("%d",&columns);

    table = malloc(sizeof(int *) * rows);
    penalty_of_row = malloc(sizeof(int *) * rows);
    penalty_of_col = malloc(sizeof(int *) * columns );

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


    if (supply_sum == demand_sum ){
    	printf("Table is balanced \n");
        // minimum_cost = FindMinimumCost(rows, columns, table);
        printf("Calculating penalty \n");
        minimum_cost  = DoUntilFindMinimumCost(rows,columns,table,penalty_of_row,penalty_of_col,minimum_cost);
	}
	
	else if (supply_sum < demand_sum ) { // if supply is less then add dummy row in table2
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

        // minimum_cost = FindMinimumCost(rows+1, columns, table2);
        rows = rows +1;
        
        printf("Now table is \n ");
        for( i = 1 ; i<= rows; i++){
            for(j = 1; j <= columns ; j++){
                printf("%d      ",table2[i][j]);
            }
            printf("\n");
        }

        printf("Calculating penalty \n");
        minimum_cost  = DoUntilFindMinimumCost(rows,columns,table2,penalty_of_row,penalty_of_col,minimum_cost);
    
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
        columns = columns + 1;
        printf("Now table is \n ");
        for( i = 1 ; i<= rows; i++){
            for(j = 1; j <= columns ; j++){
                printf("%d      ",table2[i][j]);
            }
            printf("\n");
        }

        printf("Calculating penalty \n");
        minimum_cost  = DoUntilFindMinimumCost(rows,columns,table2,penalty_of_row,penalty_of_col,minimum_cost);
	}
			
    printf("\n Minimum cost is : %d", minimum_cost);

    return 0;
}

