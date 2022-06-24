#include "veo.h"
#include <set>
#include <iterator>
#include<string>
#include <omp.h>


using namespace std;

int thread_count;
vector<pair<int,int>>pairs;

pthread_mutex_t lock1;
void* task(void* rank);
int out[10000];
// For parsing the input graph dataset
void parseGraphDataset(ifstream &inp, vector<Graph> &graph_dataset, int &dataset_size);

// Sorts vertex and edge set of graph dataset
void sortGraphDataset(vector<Graph> &graph_dataset);

// Returns the time from start to end in seconds
unsigned long long int clocksTosec(chrono::high_resolution_clock::time_point start, chrono::high_resolution_clock::time_point end);

// Displays the memory used by the program(in MB)
double memoryUsage();

// prints correct usage of program in case of an error
void usage(); 

// $ ./naive inp-file simScore_threshold dataset-size res-file

int min_size=100000;  // min graph size in dataset.  Usd to convert ged to threshold
double simfunc(int g1,int g2);
//unordered_set<unsigned> v_label;
unordered_set<unsigned> e_label;
//Taking as ordered_set. set bcoz duplicates are not allowed. ordered bcoz I need in Increasing order.
set<char> global_vrtxlbl_set;
unordered_map<char, unsigned> global_vrtxlbl_map;  //to map global vertex label to unsigned numeric.
unordered_map<string, unsigned> global_edgetype_map;
vector<Graph> graph_dataset;



// these 2 to count unique labels across all graph dataset

int main(int argc, char const *argv[])
{
	if(argc!=5)
		usage();
	//int GED = stod(argv[2]);  // threshold to write only those graph pairs to all_graph_file.txt
	double simScore_threshold =stod(argv[2]);
	int dataset_size = stoi(argv[3]); // size of input dataset
	const string res_dir = argv[4]; // directory in which all stat files would be stored
	//cout << dataset_size;

	




	mkdir(res_dir.c_str(),0777);
	mkdir((res_dir+"/graph_details/").c_str(),0777);
	graph_dataset.clear();

	ifstream dataset_file(argv[1]);
	if(!dataset_file.is_open())
	{
		cerr << "Unable to open dataset file" << endl;
		exit(0);
	}

	// parsing input dataset 
	parseGraphDataset(dataset_file, graph_dataset, dataset_size);
	cout << argv[1] << ": Graph Dataset parsed." << endl;

	//cout << 1;


	sortGraphDataset(graph_dataset); // to sort vertex and edge set
	cout << "All graphs in dataset sorted." << endl;
    
	

	ofstream all_graph_file("./"+res_dir+"/all_graph_file.txt");
	all_graph_file.close();
/*******************************************************************************************/
/***    Changing The Code                                                             ******/
    //double simScore_threshold = (1.0*min_size)/(2*(1.0*min_size)+GED)*200.0;   ///////////// Converting GED to threshold
	//double simScore_threshold = (1.0 * (1- (GED + highest_deg)/min_size) *100.0);	
	//double simScore_threshold = (1- ((1.0*GED*(1+10))/min_size)) *100.0;
	simScore_threshold = floor(simScore_threshold);

	// Result-set for each graph as vector of other graph's gid and their similarity score as double
	vector<pair<unsigned, double>> g_res; // stores graph pair with the score of a specific graph
	vector<unsigned long long int> g_time(graph_dataset.size()); // stores time required for each graph in the dataset
	unsigned long long int global_time = 0; // total time taken for similarity computation 
	// Freq of simScore with range of 1% 0-1, 1-2, 1-3, ... 99-100% 
	vector<int> score_freq(102,0); // stores sim-score frequency distribution of a particular graph
	vector<long long int> global_score_freq(102, 0); // stores sim-score frequency distribution of the dataset

	//double simScore; // similarity score
	unsigned long long int simPairCount = 0; // no. of graph pairs having similarity score > threshold

 	// timestamping start time
	chrono::high_resolution_clock::time_point cl0 = chrono::high_resolution_clock::now();

	// For clock-time calculation
	chrono::high_resolution_clock::time_point clTemp0, clTemp1; 

	vector<pair<int,int>>similarity_pairs;
	int nthreads, tid;
       // #pragma omp parallel private(nthreads, tid)      // Start of Parallelization
       // {
       // #pragma omp for

	long thread;
    pthread_t* thread_handles;
	

	thread_count = stol(argv[5]);

	for (int i = 0; i < 1000; i++)
	{
		out[i] = 0;
	}
	
	cout << "Hi" << endl;

	
	
	for(int g1 = 1; g1<graph_dataset.size(); g1++)
	{
		

		clTemp0 = chrono::high_resolution_clock::now();
		

		for(int g2 = g1-1; g2 >= 0; g2--)
		{

			// Similarity Calculation...
			double common = 0;

			//cout << 1;
			//double simScore = computeSimilarity(graph_dataset[g1], graph_dataset[g2], common,  e_label);
			similarity_pairs.push_back({g1,g2});
            // cout << simScore << endl;
			// Incrementing count... 
			
		}
		
		clTemp1 = chrono::high_resolution_clock::now();
		g_time[g1] = clocksTosec(clTemp0,clTemp1); // graph's similarity calculation time
		global_time += g_time[g1]; // dataset's similarity calculation time
		//cout<<"Inner graph loop done "<<g1<<"  "<<graph_dataset[g1].gid<<" \n";
		// Creating Result Files for graph g1
		ofstream gfile;
		all_graph_file.open("./"+res_dir+"/all_graph_file.txt",ios::app);
		gfile.open("./"+res_dir+"/graph_details/g_"+to_string(g1)+"_"+to_string(graph_dataset[g1].gid)+"_sim.txt");

		// Writing the result-set for each graph to the file for each graph
		gfile << g_res.size() << endl;
		for(auto g_iter = g_res.begin(); g_iter != g_res.end(); g_iter++)
		{
			gfile << graph_dataset[g1].gid << " " << g_iter->first << " " << g_iter->second << endl;
			all_graph_file << graph_dataset[g1].gid << " " << g_iter->first << " " << g_iter->second << endl;
		}
		g_res.clear();
		all_graph_file.close();

		// Writing g1's simScore-freq
		// for simScore==0
		gfile << "0 " << score_freq[0] << endl;
		score_freq[0] = 0;
		for(int i=1; i<101; i++)
		{
			gfile << i << " " << score_freq[i] << endl;
			score_freq[i] = 0;
		}
		// for simScore==100
		gfile << "101 " << score_freq[101] << endl; 
		score_freq[101] = 0;
		gfile << g_time[g1] << endl;
		gfile << global_time << endl;
		gfile.close();
	}
	
	
	thread_handles = (pthread_t*)malloc(thread_count*(sizeof(pthread_t)));
	pairs = similarity_pairs;
	pthread_mutex_init(&lock1,NULL);
    for(thread =0;thread < thread_count;thread++){
		
        pthread_create(&thread_handles[thread],NULL,task,(void*)thread);
    }

	for(thread=0;thread<thread_count;thread++){
        pthread_join(thread_handles[thread],NULL);
    }

	for(int i=0;i<pairs.size();i++){
		cout << out[i] << endl;
	}

/*	 ifstream ifp("2k_gsim23.txt");  
	unsigned i,j,ged,cot=0;
    while(ifp>>i and  ifp>>j and ifp>>ged){
		//if((temp.find(i)!=temp.end() && temp[i],find(j)!=temp[i].end()))
		if(temp[i][j]==2 and temp[j][i]==2)
		{ cot++;}
		else{
			cout<<i<<" "<<j<<"\n";
			cout<<"not found\n";
		}
            
        }cout<<"all matche "<<cot<<endl;
*/
	 
	 
	 // timestamping end time
	chrono::high_resolution_clock::time_point cl1=chrono::high_resolution_clock::now();	
	
	cout << "GSimJoin: VEO Similarity(naive)" << endl;
	cout << "Dataset size: " << dataset_size << endl;
	cout << "Similarity Score Threshold: " << simScore_threshold << endl;
	cout << "Similar Graph Pairs: " << simPairCount << endl;
	cout << "Memory used: " << memoryUsage() << " MB" << endl;
	cout << "Similarity Time: "<< global_time << " milliseconds" << endl;
	cout << "Total Time Taken: "<< (clocksTosec(cl0,cl1))  << " milliseconds" << endl;

	ofstream stat_file("./"+res_dir+"/stat_final.txt");
	stat_file << "GSimJoin: VEO Similarity(naive)" << endl;
	stat_file << "Dataset size: " << dataset_size << endl;
	stat_file << "Similarity Score Threshold: " << simScore_threshold << endl;
	stat_file << "Similar Graph Pairs: " << simPairCount << endl;
	stat_file << "Memory used: " << memoryUsage() << " MB" << endl;
	stat_file << "Similarity Time: "<< global_time << " milliseconds" << endl;
	stat_file << "Total Time Taken: "<< (clocksTosec(cl0,cl1))  << " milliseconds" << endl;
	stat_file.close();
	
	ofstream freq_file("./"+res_dir+"/freq_distr_file.txt");
	// for simScore==0
	freq_file << "0 " << global_score_freq[0] << endl; 
	for(int i=1; i<101; i++)
		freq_file << i << " " << global_score_freq[i] << endl;
	// for simScore==100
	freq_file << "101 " << global_score_freq[101] << endl; 
	freq_file.close();

	return 0;
}

double simfunc(int g1,int g2){
	double common = 0.0;
	double simScore = computeSimilarity(graph_dataset[g1], graph_dataset[g2], common,  e_label);


	
}

void* task(void* rank){
	long m = pairs.size();

    long my_rank = (long) rank;
    int local_m = m/thread_count;
    int my_first_row = local_m*my_rank;
    int my_last_row = (local_m)*(my_rank+1) - 1;

	for(int i=my_first_row;i<=my_last_row;i++){
		out[i] = simfunc(pairs[i].first,pairs[i].second);

	}
	return NULL;

}
// For parsing the input graph dataset
void parseGraphDataset(ifstream &dataset_file, vector<Graph> &graph_dataset, int &dataset_size)
{
	int i=0,size, vlblCount;
	unsigned vlbl_unsigned =0, edge_type_unsign =0;
	dataset_file >> size;
	dataset_file >> vlblCount; 
	if(dataset_size == -1)
		dataset_size = size;
	for(int i=0; i<vlblCount; i++)
	{
		char vlbl_char;
		dataset_file >>vlbl_char;
		cout<<vlbl_char<<" Vertex label read \n";
		global_vrtxlbl_set.insert(vlbl_char);
	}
	/*for(char lbl: global_vrtxlbl_set)
	{	cout<<lbl<<" ";
		global_vrtxlbl_map[lbl] =vlbl_unsigned++;
	}  */

	set<char>::iterator itr;
   
  	for (itr = global_vrtxlbl_set.begin(); itr != global_vrtxlbl_set.end(); itr++)
	{

		char lbl = *itr;
		//cout<<lbl<<" ";
		global_vrtxlbl_map[lbl] =vlbl_unsigned++;
		set<char>::iterator itr2 ;//=itr;
		for(itr2 =itr; itr2 != global_vrtxlbl_set.end(); itr2++)
		{
			char lbl2 =*itr2;
			string edge_type_str{lbl,  '-' , lbl2};
			cout<<lbl2<<"  "<<edge_type_str<<endl;
			global_edgetype_map[edge_type_str] = edge_type_unsign++;		
		}
	
	}

	cout<<endl;
	graph_dataset.resize(dataset_size);
	cout<<"dataset_size "<<dataset_size<<endl;

	for(auto g_iter = graph_dataset.begin(); g_iter != graph_dataset.end(); g_iter++)
	{	
		if(i <dataset_size)
		{
			g_iter->readGraph(dataset_file, vlblCount,  global_vrtxlbl_map, global_edgetype_map, e_label);
			//cout<<"i and  g_iter->gid = "<<i<<"  "<<g_iter->gid<<endl;
			i++;
			min_size = min(min_size, (int)g_iter->vertexCount+(int)g_iter->edgeCount);
		}
	}
	
/*	VertexLabelVectr.resize(vlblCount, 0);
	for(int i=0; i<vrtxLbl.size(); i++)
	{
		unsigned vlbl = global_vrtxlbl_map[vrtxlbl[i]];
		VertexLabelVectr[vlbl]++;
	}
*/

}

// Sorts vertex and edge set of graph dataset

void sortGraphDataset(vector<Graph> &graph_dataset)
{
	cout<<"graph_dataset.size() = "<<graph_dataset.size()<<endl;
	for(int i = 0; i < graph_dataset.size(); i++)
	{
		//// sort vertex-set ON BASIS OF LABELS
		sort(graph_dataset[i].vertices.begin(), graph_dataset[i].vertices.end(),    
		[&] (const int a, const int b) {return graph_dataset[i].vid_to_vc[a] < graph_dataset[i].vid_to_vc[b];}); 
		
		// edges are sorted on bases of labels only as it contains nothing but label ascii values.
		sort(graph_dataset[i].edges.begin(), graph_dataset[i].edges.end()); // sort edge-set
	}
}

// Returns the time from start to end in seconds
unsigned long long int clocksTosec(chrono::high_resolution_clock::time_point start, chrono::high_resolution_clock::time_point end)
{
	return (unsigned long long int)(1e-6*chrono::duration_cast<chrono::nanoseconds>(end - start).count());
}

// Displays the memory used by the program(in MB)
double memoryUsage()
{
	struct rusage r_usage;
	getrusage(RUSAGE_SELF, &r_usage);
	return r_usage.ru_maxrss/1024.0;
}

void usage()
{
	cerr << "usage: ./naive inp-file simScore_threshold dataset-size res-file" <<endl;
	exit(0);
}
