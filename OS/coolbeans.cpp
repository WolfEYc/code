//Christian Schuering - Assignment 1
//PSID 1932884

//Program evaluates job queues and implements a FIFO basis of a waiting list for jobs

#include <iostream>
#include <vector>

using namespace std;


void core_request(int how_long, int jobID, vector<int>& Cqueue, int &current_time, bool &core, int& core_use)
{

    if(core == true) //true == free
    {
        Cqueue.push_back(jobID);
        core = false; //false == busy
        //schedule CORE completion at time
        
        cout << "-- Job " << jobID << " requests a core at time " << current_time << " ms for " << how_long << " ms." << endl;
        //current_time = current_time + how_long;
        core_use += how_long;
    }else{
        Cqueue.push_back(jobID);
        cout << "-- Job " << jobID << " requests a core at time " << current_time << " ms for " << how_long << " ms." << endl;
        cout << "-- Job "<< jobID << " must wait for a core."<<endl;
        cout << "-- Ready queue now contains " << Cqueue.size() << " job(s) waiting for a core."<<endl;
        //current_time = current_time + how_long;
        core_use += how_long;
    }
} //core_request

//change to int to return completion time?
bool core_release(int how_long, int jobID, vector<int>& Cqueue, int &current_time, bool &core, vector<int>& jobTimes)
{
    if(!Cqueue.empty())
    {
        Cqueue.erase(Cqueue.begin());
        //current_time = current_time + how_long; //how_long == jobID
        core = true;
        cout << "-- Job " << jobID << " will release a core at time " << current_time+how_long << " ms." << endl;
        if(how_long == 0)
            cout << "-- Job " <<jobID <<" immediately returns to the ready queue." << endl;
        jobTimes[jobID-1] = how_long;
        return true;
    }
    //process next job request for job jobID
} //core_release

void disk_request(int how_long, int jobID, vector<int>& Dqueue, int &current_time, bool &disk)
{
    if(disk == true) //true == free
    {
        Dqueue.push_back(jobID);
        disk = false; //false == busy
        //schedule DISK completion event at time        
        cout << "-- Job " << jobID << " requests disk access at time " << current_time << " ms for " << how_long << " ms." << endl;
        //current_time = current_time + how_long;
    }else{
        Dqueue.push_back(jobID);
        cout << "-- Job " << jobID << " requests disk access at time " << current_time << " ms for " << how_long << " ms." << endl;
        cout << "-- Job "<< jobID << " must wait for the disk."<<endl;
        cout << "-- Ready queue now contains " << Dqueue.size() << " job(s) waiting for the disk."<<endl;
        //current_time = current_time + how_long;
    }
} // disk_request

bool disk_release(int how_long, int jobID, vector<int>& Dqueue, int &current_time, bool &disk, vector<int>& jobTimes)
{
    if(!Dqueue.empty())
    {
        Dqueue.erase(Dqueue.begin());
        //current_time = current_time + how_long; //how_long == jobID
        disk = true;
        cout << "-- Job " << jobID << " will release the disk at time " << current_time << " ms." << endl;
        if(how_long == 0)
            cout << "-- Job " <<jobID <<" immediately returns to the ready queue." << endl;
        jobTimes[jobID-1] = how_long;
        
        return true;
        
    }
    //process next job request for job jobID
} //disk_release

void spooler_request(int how_long, int jobID, vector<int>& Squeue, int &current_time, bool &spooler)
{
    if(spooler == true) //true == free //should be spooler bool?
    {
        Squeue.push_back(jobID);
        spooler = false;
        //schedule SPOOLER completion event at time
        
        cout << "-- Job " << jobID << " requests spooler access at time " << current_time << " ms for " << how_long << " ms." << endl;
        //current_time = current_time + how_long;
    }else{
        Squeue.push_back(jobID);
        cout << "-- Job " << jobID << " requests spooler access at time " << current_time << " ms for " << how_long << " ms." << endl;
        cout << "-- Job "<< jobID << " must wait for the spooler."<<endl;
        cout << "-- Spooler queue now contains " << Squeue.size() << " job(s) waiting for the spooler."<<endl;
        
    }
} //spooler_request

bool spooler_release(int how_long, int jobID, vector<int>& Squeue, int &current_time, bool &spooler, vector<int>& jobTimes)
{
    if(!Squeue.empty())
    {
        Squeue.erase(Squeue.begin());
        //current_time = current_time + how_long;
        spooler = true;
        cout << "-- Give spooler to process "<< jobID <<" from the spooler queue."<<endl;
        cout << "-- Spooler queue now contains " << Squeue.size() << " job(s) waiting for the spooler."<<endl;
        cout << "-- Job " << jobID << " will release the spooler at time " << current_time+how_long << " ms." << endl;
        if(how_long == 0)
            cout << "-- Job " <<jobID <<" immediately returns to the ready queue." << endl;

        jobTimes[jobID-1] = how_long;

        return true;
    }
    //process next job request for job jobID
} //spooler_release


int maxRowLength(vector<vector<pair<string,int>>> v){
    vector<int> temp;
    for(auto i:v)
        temp.push_back(i.size());
    
    int max = 0;
    for(int i:temp)
        if(max<i)
            max=i;
    return max;
}

bool procDone(vector<vector<pair<string,int>>> v, vector<int> rowIt,int row){
    return rowIt[row]>=v[row].size();
}

int jobStatus(int currentJob, vector<int> CQ, vector<int> SQ, vector<int> DQ,vector<int> jobTimes){

    if(jobTimes[currentJob]==-1)
        return -1;
    if(jobTimes[currentJob]==-2)
        return -2;

    for(int c: CQ)
        if(c == currentJob)
            return 1;
    for(int s: SQ)
        if(s == currentJob)
            return 1;
    for(int d:DQ)
        if(d == currentJob)
            return 1;

    if(jobTimes[currentJob]!=0)
        return 3; // running

    return 0; // ready
}

void printTerminate(int completedtime, int terminatedJob, int numofJobsproccing,vector<int> CQ, vector<int> SQ, vector<int> DQ,vector<int>& jobTimes) //i poses as the job number
{
    
    cout << endl;
    cout << "Job " << terminatedJob << " terminates at time " << completedtime << " ms." << endl;
    cout << "Job Table:" << endl;
    cout << "Job "<<terminatedJob << " is TERMINATED."<<endl;
    jobTimes[terminatedJob-1] = -1;
    for(int i = terminatedJob;i < numofJobsproccing ; i++){
        int thisjobstatus = jobStatus(i,CQ,SQ,DQ,jobTimes);
        cout << "Job "<<i+1;
        if(thisjobstatus == 1){
            cout<<" is BLOCKED."<<endl;
        }else if (thisjobstatus == 3){
            cout << " is RUNNING."<<endl;
        }else{
            cout << " is READY."<<endl;
        }
    }
    
}

bool done(vector<int> JobTimes){
    for(int i:JobTimes)
        if(i!=-2)
            return false;
    return true;
}

bool addNext(vector<int> JobTimes,int MPL){
    int counter = 0;
    for(int i:JobTimes){
        if(i>0){
            counter++;
        }
    }
        
    return counter < MPL;
}

int main()
{
    //head node is the 0th node when starting
    //node* head;

    //linecounter = jobstarting number && linecounter = jobending number
    //linecounter* head;

    vector<vector<pair<string,int>>> processes;

    

    //vector<string> veckeyword; //keyword
    //vector<int> vecargument; //argument
    //vector<int> jobnumber; //iterates anytime a new job is issued
    //vector<int> expectedtimeforjob; //pushes expected time for each new job

    //vector holders to find if we have something in the core or not
    vector<int> Disk_queue;
    vector<int> Spooler_queue;
    vector<int> Core_queue;

    //array holds core, disk and spooler;
    string keyword;
    string argument;

    //bools if theyre ready or not
    bool disk = true; //true means ready //false means busy
    bool core = true; //true means ready //false means busy
    bool spooler = true; //true means ready //false means busy
    bool terminate = false; //true means a job is terminating

    //counter for expected time finish
    int time_taken = 0;

    //holds job number
    int jobID = 1; //always start at job # 1
    int jobcounter = 0;

    //count for all disks and cores added
    int diskcounter = 0;
    int corecounter = 0;
    int core_use = 0;

    int MPL;
    string gaybitch;
    cin>>gaybitch>>MPL;
    //cout << MPL;
    while(cin >> keyword >> argument)
    {
        pair<string,int> addthis(keyword,stoi(argument));
        //cout << keyword << argument << endl;
        //addnode(head, keyword, argument);
        //veckeyword.push_back(keyword);
        //int hold = stoi(argument);
        //vecargument.push_back(stoi(argument));

        if(keyword == "JOB"){
            vector<pair<string,int>> newjob;
            newjob.push_back(addthis);
            processes.push_back(newjob);
        }else{
            processes[processes.size()-1].push_back(addthis);
        }
    }
    int bscounter = 0;
    cout << "/////////////////////////////////////" << endl;

    int maxLength = maxRowLength(processes);

    vector<int> currentIterationofeachrow(processes.size());

    vector<int> JobTimes(processes.size(),-1);

    int current_job = 0;

while(!done(JobTimes)){


        if(procDone(processes,currentIterationofeachrow,current_job)){
            
            int sum = 0;
            for(int i:JobTimes)
                if(i != -1)
                    sum++;
            
            JobTimes[current_job] = -2;
            jobcounter++;
            current_job = jobcounter;
            printTerminate(time_taken, current_job+1,sum,Core_queue,Spooler_queue,Disk_queue,JobTimes);
            continue;
        }



        //equation start
        //cout << veckeyword[current_job] + " ";
        //cout << vecargument[current_job];
        //cout << endl;
        //this works^

        

        string processName = processes[current_job][currentIterationofeachrow[current_job]].first;
        int number = processes[current_job][currentIterationofeachrow[current_job]].second;


        if(processName == "PRINT")
        {
            currentIterationofeachrow[current_job]++;
            spooler_request(number, jobID, Spooler_queue, time_taken, spooler);
        }
        else if(processName == "CORE")
        {
            currentIterationofeachrow[current_job]++;
            corecounter++;
            core_request(number, jobID, Core_queue, time_taken, core, core_use);
        }
        else if(processName == "DISK")
        {
            diskcounter++;
            currentIterationofeachrow[current_job]++;
            disk_request(number, jobID, Disk_queue, time_taken, disk);
        }
        else if(processName == "JOB") //takes in the job #
        {
            

            jobID = current_job+1;
            //jobnumber.push_back(vecargument[current_job]);

            cout << endl << endl;
            cout << "Job " << jobID << " is fetched at time " << time_taken << " ms" << endl;
            
            cout << "Job Table: " << endl;
            
            bool flag = 0;
            for(int i = 0;i<processes.size();i++){
                if(JobTimes[i]!=-1)
                    flag = 1;
            }
            if(flag == 0){
                cout << "There are no active jobs."<<endl;
            }else{
                for(int i = 0;i < processes.size() ; i++){
                    int thisjobstatus = jobStatus(i,Core_queue,Spooler_queue,Disk_queue,JobTimes);
                    if(thisjobstatus != -1){
                        cout << "Job "<<i+1;
                        if(thisjobstatus == 1){
                            cout<<" is BLOCKED."<<endl;
                        }else if (thisjobstatus == 3){
                            cout << " is RUNNING."<<endl;
                        }else{
                            cout << " is READY."<<endl;
                        }
                    }
                }
            }           
            cout << endl;
            currentIterationofeachrow[current_job]++;
            JobTimes[current_job] = 0;
            
            

            /*int time_complexity_iteration = current_job;
            while(veckeyword[time_complexity_iteration] != "JOB") // then iterates through the keywords, while at the same time ignoring the keyword JOB
            {
                time_taken_for_all += (vecargument[time_complexity_iteration]); //adding the arguments up until the next job
                //cout << time_taken_for_all << " ";
                time_complexity_iteration++;
                if(veckeyword[time_complexity_iteration] == "JOB")
                {
                    cout << time_taken_for_all << " ";
                    expectedtimeforjob.push_back(time_taken_for_all); //giving an expected time completion for each new job
                }
            }*/
        }

        if (spooler_release(processes[current_job][currentIterationofeachrow[current_job]].second, current_job+1, Spooler_queue, time_taken, spooler,JobTimes) == false); //must set to be true
        if (core_release(processes[current_job][currentIterationofeachrow[current_job]].second, current_job+1, Core_queue, time_taken, core,JobTimes) == false); //must set to be true
        if (disk_release(processes[current_job][currentIterationofeachrow[current_job]].second, current_job+1, Disk_queue, time_taken, disk,JobTimes) == false); //must set to be true
        //for all 3 of these, implenet a jobqueue that pops when the releases are called, and pushed when the requests are called
        //cout << bscounter++ << endl; //loops through 148 times for input10.txt


            if(addNext(JobTimes,MPL) && processName != "JOB"){
                jobcounter++;
                current_job = jobcounter;
            }else{
                int min = 0;
                for(int i = 1; i<JobTimes.size(); i++)
                    if((JobTimes[i]<JobTimes[min] && JobTimes[i]>0 ) || (JobTimes[i]>0 && JobTimes[min]<=0))
                        min = i;
                
                int minval = JobTimes[min];

                if(minval<0)
                    minval = 0;
                        
                time_taken+=minval;

                for(int i = 0; i<JobTimes.size(); i++)
                    if(JobTimes[i]>0)
                        JobTimes[i]-=minval;

                current_job = min;
                
            }
        }
    
    cout << endl;

    float coresadded = 0;

    cout << "SUMMARY:" << endl;
    cout << "Totaly elapsed time: " << time_taken << " ms" << endl;
    cout << "Number of jobs that completed: " << jobID << endl;
    cout << "Total number of disk access: " << diskcounter << endl;
    cout << "CPU utilization: ";
    printf("%.3f",(float)(core_use)/(float)(time_taken));
    cout << endl; //add up entire elapsed time and divide core times added by the entireelapsed time
                                    //maybe just use (float coresadded = coreutilization/expectedtimeforjob[i];)

    return 0;
}
//get timer working
//3 queues
//add time each process finishes at and divide it by number of jobs = computing itme;
//total simulation time in ms - 
//number of jobs that have been completed - 
//total number of disc requests - 
//cpu utilization, fraction of time device was busy between 0 and 1 -
//must use strings, manipulate when changing to ints then change back to strings for final output
//have multiple vectors, possibly use priority queue, sort vectors with multiple copies of jobs depending on the MPL size
//say we have an MPL 3, have vectors with every job and sort them using for loops