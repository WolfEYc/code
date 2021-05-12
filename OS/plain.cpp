#include <iostream>
#include <queue>
#include <vector>
using namespace std;

queue<pair<int,int>> Disk_q, Spooler_q, Core_q;

vector<queue<pair<string,int>>> processes;

int total_time = 0, disk_accesses = 0,
    core_accesses = 0, core_time_used = 0,
    MPL, current_job = 0, *JobTimes,
    argument,jobCount=0, jobCounter=0;

int core =-1,disk=-1,spooler=-1;

string keyword;

bool done(){
    for(int i = 0;i<jobCount;i++)
        if(JobTimes[i]!=-2)
            return false;
    return true;
}

vector<int> activeProcceses(){
    vector<int> v;
    for(int i = 0;i<jobCount;i++)
        if(JobTimes[i]>=0 || JobTimes[i]==-3)
            v.push_back(i);
    return v;
}

vector<int> runningProcceses(){
    vector<int> v;
    for(int i = 0;i<jobCount;i++)
        if(JobTimes[i]>=0)
            v.push_back(i);
    return v;
}

void core_request(int job,int how_long){
    pair<int,int> newReq (job,how_long);
    Core_q.push(newReq);
    cout << "-- Job " << job+1 << " requests a core at time "
        << total_time << " ms for " << how_long << " ms." << endl;
    
    if(core != -1 || Core_q.size()>1){
        cout << "-- Job "<< job+1 << " must wait for a core."<<endl
         << "-- Ready queue now contains " << Core_q.size() << " job(s) waiting for a core."<<endl;
        JobTimes[job]=-3;
    }
}

void core_release(){
    if(!Core_q.empty() && core==-1){
        
        int job = Core_q.front().first;
        int how_long = Core_q.front().second;
        core = job;
        Core_q.pop();

        cout << "-- Job " << job+1 << " will release a core at time "
         << total_time+how_long << " ms." << endl;
        
        if(how_long == 0){
            cout << "-- Job "<< job+1
                <<" immediately returns to the ready queue." << endl;
        }
        if(JobTimes[job]>0)
            total_time+=JobTimes[job];
        JobTimes[job] = how_long;
    }
}

void disk_request(int job,int how_long){
    pair<int,int> newReq (job,how_long);
    Disk_q.push(newReq);
    cout << "-- Job " << job+1 << " requests disk access at time "
        << total_time << " ms for " << how_long << " ms." << endl;
    
    if(disk!=-1 || Disk_q.size()>1){
        cout << "-- Job "<< job+1 << " must wait for the disk."<<endl
         << "-- Ready queue now contains " << Disk_q.size() << " job(s) waiting for the disk."<<endl;
        JobTimes[job]=-3;
    }

}

void disk_release(){
    if(!Disk_q.empty() && disk==-1){        
        int job = Disk_q.front().first;
        int how_long = Disk_q.front().second;
        disk = job;
        Disk_q.pop();

        cout << "-- Job " << job+1 << " will release the disk at time "
         << total_time+how_long << " ms." << endl;
        
        if(how_long == 0){
            cout << "-- Job "<< job+1
                <<" immediately returns to the ready queue." << endl;
        }
        if(JobTimes[job]>0)
            total_time+=JobTimes[job];
        JobTimes[job] = how_long;
    }
}

void spooler_request(int job,int how_long){
    pair<int,int> newReq (job,how_long);
    Spooler_q.push(newReq);
    cout << "-- Job " << job+1 << " requests the spooler at time "
        << total_time << " ms for " << how_long << " ms." << endl;
    
    if(spooler != -1 || Spooler_q.size()>1){
        cout << "-- Job "<< job+1 << " must wait for the spooler."<<endl
         << "-- Ready queue now contains " << Spooler_q.size() << " job(s) waiting for the spooler."<<endl;
        JobTimes[job]=-3;
    }
}

void spooler_release(){
    if(!Spooler_q.empty() && spooler==-1){
        
        int job = Spooler_q.front().first;
        int how_long = Spooler_q.front().second;
        spooler = job;
        Spooler_q.pop();

        cout << "-- Job " << job+1 << " will release the spooler at time "
         << total_time+how_long << " ms." << endl;
        
        if(how_long == 0){
            cout << "-- Job "<< job+1
                <<" immediately returns to the ready queue." << endl;
        }
        if(JobTimes[job]>0)
            total_time+=JobTimes[job];
        JobTimes[job] = how_long;
    }
}

void printTerminate(int terminatedJob) 
{
    
    cout << endl;
    cout << "Job " << terminatedJob << " terminates at time " << total_time << " ms." << endl;
    cout << "Job Table:" << endl;
    cout << "Job "<<terminatedJob << " is TERMINATED."<<endl;

    vector<int> active = activeProcceses();

    for(int i = 0;i < active.size(); i++){
        int thisjobstatus = JobTimes[i];
        cout << "Job "<<active[i]+1;
        if(thisjobstatus == -3){
            cout<<" is BLOCKED."<<endl;
        }else if (thisjobstatus > 0){
            cout << " is RUNNING."<<endl;
        }else{
            cout << " is READY."<<endl;
        }
    }
    cout << endl;
    
}


int main(){

    cin >> keyword >> MPL;

    while(cin >> keyword >> argument)
    {
        pair<string,int> addthis(keyword,argument);

        if(keyword == "JOB"){
            queue<pair<string,int>> newjob;
            newjob.push(addthis);
            processes.push_back(newjob);
            jobCount++;
        }else{
            processes.back().push(addthis);
        }        
    }
    cout << "/////////////////////////////////////" << endl;

    JobTimes = new int[jobCount];

    for(int i = 0;i<jobCount;i++)
        JobTimes[i] = -1;

    while(!done()){       

        if(processes[current_job].empty()){
            if(JobTimes[current_job]>0)
                total_time+=JobTimes[current_job];
            JobTimes[current_job] = -2;
            printTerminate(current_job+1);

            //cout << jobCounter << " < " << jobCount<<endl <<endl;

            if(jobCounter<jobCount){
                current_job = jobCounter;
            }else{
                if(done())
                    break;
                current_job = activeProcceses().front();
            }
            continue;
        }       

        string pName = processes[current_job].front().first;
        int how_long = processes[current_job].front().second;

        processes[current_job].pop();

        if(pName == "PRINT"){
            spooler_request(current_job,how_long);
        }
        if (pName == "CORE"){
            core_accesses++;
            core_time_used+=how_long;
            core_request(current_job,how_long);

        }if (pName == "DISK"){
            disk_accesses++;
            disk_request(current_job,how_long);
        }
        if(pName == "JOB"){
            
            cout << endl << "Job " << current_job+1 << " is fetched at time " << total_time << " ms"
                << endl << "Job Table: " << endl;

            vector<int> active = activeProcceses();
            if(active.size()==0)
                cout << "There are no active jobs."<<endl;
            else{
                for(int i = 0;i < active.size(); i++){
                    int thisjobstatus = JobTimes[active[i]];
                    cout << "Job "<< active[i]+1;
                    if(thisjobstatus == -3){
                        cout<<" is BLOCKED."<<endl;
                    }else if (thisjobstatus > 0){
                        cout << " is RUNNING."<<endl;
                    }else{
                        cout << " is READY."<<endl;
                    }
                }
            }
            cout << endl;
            jobCounter++;
            JobTimes[current_job] = 0;
        }else{        

            core_release();
            disk_release();
            spooler_release();  

            vector<int> active = runningProcceses();
            int min = 0; //lowest ready job
            for(int i = 1;i<active.size();i++){
                if(JobTimes[active[i]]<JobTimes[active[min]])
                    min = i;
            }            

            int minJob = active[min];
            int lowestTime = JobTimes[minJob];
            current_job = minJob;

            if(activeProcceses().size() < MPL && jobCounter < jobCount){
            //load another job into memory
                current_job = jobCounter;
            }else{
                total_time+=lowestTime;

                for(int i = 0;i<active.size();i++){
                    JobTimes[active[i]]-=lowestTime;
                }

                if(core == current_job ){
                    core = -1;
                }if (disk == current_job){
                    disk = -1;
                }if (spooler == current_job){
                    spooler = -1;                    
                }
            }
        }
    }

    cout << "SUMMARY:" << endl;
    cout << "Totaly elapsed time: " << total_time << " ms" << endl;
    cout << "Number of jobs that completed: " << jobCounter << endl;
    cout << "Total number of disk access: " << disk_accesses << endl;
    cout << "CPU utilization: ";
    printf("%.3f",(float)(core_time_used)/(float)(total_time));
    cout << endl;

    delete JobTimes;
    return 0;
}
