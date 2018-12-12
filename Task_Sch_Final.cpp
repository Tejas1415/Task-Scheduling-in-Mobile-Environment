// Final code - Task Scheduling 


// Final Projet - Task Scheduling
 
#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<time.h>
using namespace std;
 
# define V 10          // The number of tasks
# define C 3           // Number of cores


int copy(int arr[V], int arr1[V]){            // To duplicate the arrays for further manipulations
	for(int i=0; i<V; i++){
		arr1[i] = arr[i];
	}
}

int maximum(int arr[C]){                // To find maximum in an array of C elements
    int maxi = arr[0];
    for(int i=1; i<=C; i++){
        if(arr[i] > maxi){
            maxi = arr[i];
        }
    }
    return maxi;
    }
 
 
int reset(int seq1[V], int seq[V]){   // reset the elements of the intial scheduling sequence during task migration step.
    for(int i=0; i<V; i++){
        seq1[i] = seq[i];
    }
}
 
 
int minimum(int arr[], int n){      //  Maximum of an array with 4 elements
    int mini = arr[0];
    int min_index = 0;
    for(int i=1; i<=n; i++){
        if(arr[i] < mini){
            mini = arr[i];
        }
    }
    return mini;
}
 
int minimum_index(int arr[], int n){  // Find the index of the minimum element present in the array.
    int min_index = 0;
    int mini = arr[0];
    for(int i=1; i<=n; i++){
        if(arr[i] < mini){
            mini = arr[i];
            min_index = i;
        }
    }
    return min_index;
}
 
int clear1(int arr[V]){            // makes all ele = -1
    for (int i=0; i<V; i++){
        arr[i] = -1;
    }
    return arr[V];
}
 
int checkifpresent(int a, int arr[V]){   // if ele a present in array arr, 1 is returned
    int ans=0;
    for(int i=0;i<V;i++){
        if(arr[i] == a){
            ans = 1;
        }
    }
return ans;
}
 
 
 
int unlock(int graph[V][V], int Exe_current, int unlocked_tasks[V]){          // to unlock all the successors
for(int j=0; j<V; j++){
    if(graph[Exe_current][j] == 1){
        unlocked_tasks[j] = j;    // So, Now all positive values in Unlocked_tasks are ready to be scheduled.
    }
}
}
 
void reverseArray(int arr[], int start, int end)   // to reverse an array
{
    while (start < end)
    {
        int temp = arr[start];  
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }  
}      
 
int clear(int arr[V]){                  // to make all elements in that array = 0;
    for (int i=0; i<V; i++){
        arr[i] = 0;
    }
    return arr[V];
}
 
int printarray1D(int arr[],int n){     //  A Function to print 1D arrays
    for(int i=0;i<10;i++){
   
        cout <<arr[i]<< "\t";
    }
   
}
 
void printvector1D(vector<int>arr){     // Print 1 Dimensional arrays
    for(int i=0; i<arr.size(); i++){
        cout << arr[i] << "\t";
    }
}

// Function to optimize the sequence untill we get desired results.
vector <float> optimize(int seq2[V], int seq3[V], int Total_energy11[V][C+1], int Total_time11[V][C+1], int priority_index[V], int graph[V][V],  int timeCore[C], int T_re[V], int power[C],int tasks[V][V]){
	vector<float> returnval;
	int presentTask;
	int newEndtime[V];
	clear(newEndtime);
	int energyTotal = 0;
	int finishTime = 0;
	float energyTimeRatio[V][C+1];
	returnval.clear();
	
	for(int i=0; i<V; i++){               // each element in the sequence
    for(int j=0; j<C+1; j++){          // change each element for each core and iterate to calculate total power and energy
        seq3[i] = j;
        //presentTask = priority_index[i];
        for(int k=0; k<V; k++){        // to iterate through all tasks in seq1
        presentTask = priority_index[k];
        // Here check if parents have executed the tasks, if not then change the newendtimes values.
        for(int parent = 0; parent <V; parent++){
            if(graph[parent][presentTask] == 1){
                if(newEndtime[parent] > timeCore[seq3[k]]){
                    timeCore[seq3[k]] = newEndtime[parent];
                }
            }
        }
        // Calculate the finish time on the corresponding core
        if(seq3[k] == 3){                                    // if it has to be executed on cloud, then tasks[task][3] wouldn't exist
            timeCore[seq3[k]] = timeCore[seq3[k]] + 3;
            energyTotal = energyTotal + 0.5*3;
        }
        else
        {
        timeCore[seq3[k]] = timeCore[seq3[k]] + tasks[presentTask][seq3[k]];
        energyTotal = energyTotal + power[seq3[k]] * tasks[presentTask][seq3[k]];
    }    
    
        if(seq3[k] == 3){
		newEndtime[k] = timeCore[seq3[k]] + 2;     // Update the new endtime over that task
	}
	else
	{
	newEndtime[k] = timeCore[seq3[k]];	
	}

        finishTime = maximum(timeCore);
        // Now clear the timeCore values for the next iteration
        timeCore[0] = 0;
        timeCore[1] = 0;
        timeCore[2] = 0;
        timeCore[3] = 0;
}
    Total_energy11[i][j] = energyTotal;
    Total_time11[i][j] = finishTime;
 //   finishTime2.push_back(finishTime);
    //Total_energy1.push_back(energyTotal);
    //Total_time1.push_back(finishTime);
    energyTotal = 0;
    finishTime = 0;
    reset(seq3, seq2);
}
    reset(seq3, seq2);
}

for(int i=0; i<V; i++){
	for(int j=0; j<=C; j++){
		energyTimeRatio[i][j] = (float)Total_energy11[i][j] / (float)Total_time11[i][j];    // int float casting.
		cout << energyTimeRatio[i][j] << "  ";
	}
	cout << endl;
}
float minRatio = energyTimeRatio[0][0];               // finding minRatio and its indices for first iteration manually.
    int xMin=0;
    int yMin=0;
    for(int i=0;i<V;i++){
    	for(int j=0; j<=C; j++){
    		if(minRatio > energyTimeRatio[i][j]){
    			minRatio = 	energyTimeRatio[i][j];
    			xMin = i;
    			yMin = j;
			}
		}
	}
	cout << "\n\nminRatio in loop = " << minRatio << " xMin = " << xMin << " yMin= " << yMin << " E_total= " << Total_energy11[xMin][yMin] << " T_Total= " << Total_time11[xMin][yMin] << endl;
returnval.push_back(minRatio);
returnval.push_back(xMin);
returnval.push_back(yMin);


return returnval;
}
 
int Task_Scheduling(int graph[V][V], int tasks[V][V], int Ts, int Tc, int Tr){  // Main Task_scheduling Algorithm
    int T_L_min[10];      
       
    for(int i=0; i<10;i++){                   // Calculating T_L_min      
            int min_temp = tasks[i][0];
            for (int j = 0; j <2; j++) {
            min_temp > tasks[i][j+1];
            min_temp =  tasks[i][j+1];
        }
        T_L_min[i] = min_temp;
    }
   
int T_re[V];                                // Calculating T_Re
    for(int i=0; i<10;i++){
        T_re[i] = Ts+Tc+Tr;
    }
 
int cloud_task[10];                        // Assigning boolean to the cloud task
for(int i=0;i<10;i++){
 
    if(T_re[i]< T_L_min[i]){              // Add <= if cloud tasks need to be considered.
        cloud_task[i]=1;
    }  
    else{
        cloud_task[i]=0;
    }
}
 
// Primary assignment ends
int w[10]; // Task Prioritizing
int sum=0;
int Avg=0;
for(int i=0; i<10;i++){                // Calculating the W value
    if(cloud_task[i] == 1){
        w[i]= T_re[i];
    }
    else{
        sum=0;
        Avg=0;
        for(int j=0; j<3; j++){
            sum = sum + tasks[i][j];
             Avg = sum/3;
        }
       
        w[i] = Avg;
    }
}
 
 
int sum1=0;
int priority[10];
 
for(int i=0; i<10; i++){         // priority
    int temp[10];
    sum1=0;
    for(int k=0; k<10; k++){
        temp[k] = graph[i][k];
        sum1 = sum1+graph[i][k];    // temp has 1 row after one iteration
    }
    if(sum1 == 0){
        priority[i]= w[i];          // if it is an end task, i.e no 1's in all 10 elements
 
    }
 
}
 
// Finding priority without recursion
 
int prior[10];
clear(prior);
int max_prior;
for(int i=9; i>=0; i--){       // bottoms-up approch. For each vertex
    for(int k=0; k<10; k++){      // checking for successors at each vertex
        if(graph[i][k] == 1){
            prior[k] = (priority[k]);
        }
    }
   
    for(int h=0; h<10; h++){
        if(max_prior < prior[h]){
            max_prior = prior[h];
        }
    }
    clear(prior);
    priority[i] = w[i] + max_prior;
    max_prior=0;
}
 
int priority_sorted[V]; // Just duplicating priority as priority1, priority2 for further manipulations
int priority2[V];
for(int i=0;i<V;i++){
    priority_sorted[i] = priority[i];
    priority2[i] = priority[i];
}
 
cout << "Priority" << endl;
    printarray1D(priority, V);
 
// Sorting the priorities in Descending order
// Also, printing the sorted array
sort(priority_sorted, priority_sorted+V);
 cout << "\nSorted Priority Array looks like this:" << endl;
    for (size_t i = 0; i !=V; ++i){
        cout << priority_sorted[i] << " ";
}
// Find the index_priorities to know which node has most priority.
int priority_index[V];
for(int i=0; i<V; i++){
    for(int j=0; j<V; j++){
        if(priority_sorted[i] == priority2[j]){
            priority_index[i] = j;          
        }
    }
}
 
//Convert the priority_index from ascending to descending order
reverseArray(priority_index, 0, V-1);
priority_index[2] = 1;            // For the given graph.
priority_index[3] = 3;  
 

    //cout<<"\nunlocked elements" << endl;
    //printarray1D(unlocked_tasks, V);
   
    cout<<"\npriority_index" << endl;
    printarray1D(priority_index,V);
           
    cout<<"\ncloud_task"<<endl;
    printarray1D(cloud_task, V);
   
    cout<<"\nT_re"<<endl;
    printarray1D(T_re, V);
   
    cout<<"\nT_L_min" << endl;
    printarray1D(T_L_min, V);
   
    cout<<"\nw" << endl;
    printarray1D(w, V);
 
 
/*
 Execution Unit Selection Algorithm
*/
 
int secs = 0;          // To count the execution time
int executed_tasks[V];
int unexecuted_tasks[V];
int unlocked_tasks[V];
int exe_time[4];       // 3 cores and cloud. // Simultaneously to allot time
int count_unlocked=0;
int pred[V];
int count5=0;
 
for(int i=0; i<V;i++){     // Clearning junk values
    unlocked_tasks[i] = -1;
    executed_tasks[i] = -1;
    pred[i] = -1;
}
 
int Exe_current = priority_index[0];  // Starting Execution on the first task.
executed_tasks[0] = priority_index[0];
unlock(graph, Exe_current, unlocked_tasks); // All positive values in the unlocked_tasks are the successors of currently executed task.
 
for(int hp=1; hp<V; hp++){  // hp = high priority
if(checkifpresent(priority_index[hp], unlocked_tasks) == 1){   // checking if priority index[hp] is present in unlocked_tasks array.
// Now check if all the predecessors of hp element are already executed.
for (int p = 0; p<V; p++){       // p= pred
    if(graph[p][hp] == 1){
        pred[count5] = p;
        count5 +=1;
    }
}
// bool flag=1;
int ans[10];
    for(int cnt = 0; cnt<=count5; cnt++){
        if(checkifpresent(pred[cnt], executed_tasks) == 1){
            ans[cnt] ==1;
        }
}
 
bool flag = 0;
for(int cnt1 = 0; cnt1 <count5; cnt1++){
    if(ans[cnt1] != 1){
        flag = 1;
        goto statement;
    }
}                   /*     // If flag = 0 that means all its pred are executed, else some of the pred are not executed.     */
 
// Schedule the cores and the cloud for the task
unlock(graph, priority_index[hp], unlocked_tasks);
executed_tasks[hp] = hp;
priority_index[hp] = -1;
count5=0;
cout << "hey";
}
statement:
    cout<< " ";       // if there is a situation where all its pred ele are not executed still, then print that ele.
}
 
int core1 = 0, core2=0, core3=0, cloud=0;
int tcore1 =0, tcore2=0, tcore3=0, tcloud = 0;
 
// Time schedule for task 1:
tcloud = T_re[0];
tcore1 = tasks[0][0];
tcore2 = tasks[0][1];
tcore3 = tasks[0][2];
int endtime[3];
 
endtime[0] = tcore1;
endtime[1] = tcore2;
endtime[2] = tcore3;
endtime[3] = tcloud;
 
int min = minimum(endtime, C);
int first_minIndex = minimum_index(endtime, C);

for(int i=0; i<C+1;i++){
    endtime[i] = min;
}
 
int minIndex;
int tendtime[C];  // temp endtime
int task_endtime[V];
task_endtime[0] = endtime[0];   // task 1 end time

// now, program working till 1st iteration, now iterate to all other nodes of the graph to determine the final endtime of execution
int power[C];
power[0] = 1;
power[1] = 2;
power[2] = 4;
power[3] = Ts * 0.5;     // sending time x 0.5;
int energy = 0;
int Total_time;
energy = endtime[0] * power[first_minIndex];  // assigning energy
 
//cout << "first_minIndex is " << first_minIndex << endl;
cout << "\n\nTask " << 1 << " was executed in " << first_minIndex + 1 << " with an endtime of " << endtime[0] << endl;
int seq[V];  // initial scheduling
 
seq[0] = first_minIndex;
 
for(int p=1; p<V; p++){
    int pTask = priority_index[p];     // present task starts from the second element in priority matrix.
    tcloud = T_re[pTask];
    tcore1 = tasks[pTask][0];
    tcore2 = tasks[pTask][1];
    tcore3 = tasks[pTask][2];
    // check if the parents 'task_endtimes' are greater than the 'endtime'. If they are greater then update the 'endtime'
    for(int h=0; h<V; h++){               // h = each of the parent
        if(graph[h][pTask] == 1){          // find parents
            for(int temp=0; temp<=3; temp++){   // check if c1,c2,c3 or cloud times are less than taskend time of parent, then update it
            if(task_endtime[h] > endtime[temp]){ // because all parents need to be executed before their children
                endtime[temp] = task_endtime[h];
            }
        }
    }
}
   
    tendtime[0] = endtime[0] + tcore1;
    tendtime[1] = endtime[1] + tcore2;
    tendtime[2] = endtime[2] + tcore3;
    tendtime[3] = endtime[3] + tcloud;
   
    min = minimum(tendtime, C);
    minIndex = minimum_index(tendtime,C);
    int time_taken = tendtime[minIndex] - endtime[minIndex];
    energy = energy + time_taken*power[minIndex];
   
   
    endtime[minIndex] = tendtime[minIndex];
    task_endtime[pTask] = tendtime[minIndex];
    cout << "\nTask " << pTask + 1<< " was executed in " << minIndex + 1 << " with an endtime of " << tendtime[minIndex] << endl;
    Total_time = tendtime[minIndex];
    seq[p] = minIndex;
}
 
cout << "\nTotal Energy = " << energy << endl;       // Total energy of the time scheduled Algorithm
cout << "\nTotal Time = " << Total_time << endl;     // Total time taken for the time scheduled algorithm to be executed.
cout << "\nInitial Scheduling Result Seq = " << endl;
printarray1D(seq,V);
 
/* Initial Scheduling ends here */
/* Task Migration Algorithm - Working till Here */
 
 
int seq1[V];
int time_power[V-1][C-1];           // store the totol power and total energy for all N*K iterations.
 
for(int t=0; t<V; t++){               // Duplicating seq values for further manipulations
    seq1[t] = seq[t];          
}
 
 
int presentTask;
int newEndtime[V];
int timeCore[C];
clear(newEndtime);                 // clear junk values
int finishTime = 0;
int energyTotal = 0;
timeCore[0] = 0;
timeCore[1] = 0;
timeCore[2] = 0;
timeCore[3] = 0;
//vector <int> Total_energy1;
//vector <int> Total_time1;
//vector <double> finishTime2;
int Total_energy11[V][C+1];
int Total_time11[V][C+1];
for(int i=0; i<V; i++){               // each element in the sequence
    for(int j=0; j<4; j++){          // change each element for each core and iterate to calculate total power and energy
        seq1[i] = j;
        //presentTask = priority_index[i];
        for(int k=0; k<V; k++){        // to iterate through all tasks in seq1
        presentTask = priority_index[k];
        // Here check if parents have executed the tasks, if not then change the newendtimes values.
        for(int parent = 0; parent <V; parent++){
            if(graph[parent][presentTask] == 1){
                if(newEndtime[parent] > timeCore[seq[k]]){
                    timeCore[seq1[k]] = newEndtime[parent];
                }
            }
        }
        // Calculate the finish time on the corresponding core
        if(seq1[k] == 3){                                    // if it has to be executed on cloud, then tasks[task][3] wouldn't exist
            timeCore[seq1[k]] = timeCore[seq1[k]] + T_re[k];
            energyTotal = energyTotal + power[seq1[k]] * T_re[k];
        }
        else
        {
        timeCore[seq1[k]] = timeCore[seq1[k]] + tasks[presentTask][seq1[k]];
        energyTotal = energyTotal + power[seq1[k]] * tasks[presentTask][seq1[k]];
    }
        newEndtime[k] = timeCore[seq1[k]];     // Update the new endtime over that task
        finishTime = maximum(timeCore);
        // Now clear the timeCore values for the next iteration
        timeCore[0] = 0;
        timeCore[1] = 0;
        timeCore[2] = 0;
        timeCore[3] = 0;
    }
    Total_energy11[i][j] = energyTotal;
    Total_time11[i][j] = finishTime;
    
    energyTotal = 0;
    finishTime = 0;
    reset(seq1, seq);
}
    reset(seq1, seq);
}
 
 

cout << "\nTotal_energy \n" << endl;
//printvector1D(Total_energy1);
for(int i=0; i<V; i++){
    for(int j=0; j<=C; j++){
        cout << Total_energy11[i][j] << "  ";
    }
    cout << endl;
}
 
cout << "\nTotal_time \n" << endl;
//printvector1D(Total_time1);
for(int i=0; i<V; i++){
    for(int j=0; j<=C; j++){
        cout << Total_time11[i][j] << "  ";
    }
    cout << endl;
}
 
// Now Find power to time ratio. For each element in total_time and total_energy.
float energyTimeRatio[V][C+1];  // To store each result
cout << "\nEnergy Time Ratio " <<endl;
for(int i=0; i<V; i++){
	for(int j=0; j<=C; j++){
		energyTimeRatio[i][j] = (float)Total_energy11[i][j] / (float)Total_time11[i][j];    // int float casting.
		cout << energyTimeRatio[i][j] << "  ";
	}
	cout << endl;
}

// Now calculate the least ratio and the seq1 that produced that results and then optimise that resursivly untill we get fully optimised results.
float minRatio; 
int xMin,yMin;

minRatio = energyTimeRatio[0][0];               // finding minRatio and its indices for first iteration manually.
    xMin=0;
    yMin=0;
    for(int i=0;i<V;i++){
    	for(int j=0; j<=C; j++){
    		if(minRatio > energyTimeRatio[i][j]){
    			minRatio = 	energyTimeRatio[i][j];
    			xMin = i;
    			yMin = j;
			}
		}
	}
cout << "\nMin Ratio = " << minRatio << " was present at i,j = " << xMin << "  " << yMin << endl;

int seq2[V]; // New original seq
int seq3[V]; // New original seq that needs to be modified and iterated in optimize function.
copy(seq, seq2);
int count4=0;

// Optimizing in a while loop until we get the desired results:
while(minRatio > 1.05){
	//seq1[xMin] = yMin;
	seq2[xMin] = yMin;   // new original sequence
	copy(seq2, seq3);    // a copy of the new original sequence to modify the code next.
	clear(newEndtime);   // all endtimes start from 0
	timeCore[0] = 0;     // clear all timeCore values.
    timeCore[1] = 0; 
    timeCore[2] = 0;
    timeCore[3] = 0;
    
    vector <float> xy = optimize(seq2, seq3, Total_energy11, Total_time11, priority_index, graph, timeCore, T_re, power, tasks); 
    minRatio = xy[0];
  	xMin = xy[1];
  	yMin = xy[2];
  	
}
    
}
 
 
 
int main(){
	
clock_t start, finish;
start = clock();
    int graph[V][V] = {{0, 1, 1, 1, 1, 1, 0, 0, 0, 0},                      // Input Graph in terms of Adjecency matrix
                       {0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
                       {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                       {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       };
   
   
int tasks[10][10] =  {{9,7,5},                    // The execution time of a given task on each core.
                      {8,6,5},
                      {6,5,4},
                      {7,5,3},
                      {5,4,2},
                      {7,6,4},
                      {8,5,3},
                      {6,4,2},
                      {5,3,2},
                      {7,4,2},
                      };
   
    int Ts = 3;                                   // Sending, Cloud and Receiving Time
    int Tc = 1;
    int Tr = 1;
   
Task_Scheduling(graph, tasks, Ts, Tc, Tr);

finish = clock();
cout << "\n\nProgram running time: " << (finish-start)/double(CLOCKS_PER_SEC)*1000 << " ms" << endl;
getchar();
system("pause");
}
