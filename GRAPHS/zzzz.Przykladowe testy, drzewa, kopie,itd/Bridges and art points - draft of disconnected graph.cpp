
void Graph::connectedBridgesAndArtPoints( int &dfsnum, int myNumber, int parent ){
//	cout << "JEstem w connectedBridges, dfsnum = " << dfsnum << "  myNumber = " << myNumber << "  mainNumber = " << nodes[myNumber].mainGraphNumber << endl;
	nodes[myNumber].isArtPoint = false;
	nodes[myNumber].PreOrder = dfsnum++;
	nodes[myNumber].low = nodes[myNumber].PreOrder;
	nodes[myNumber].dfssons = 0;
	
	REP( i,nodes[myNumber].size() ){
		if( nodes[ nodes[myNumber][i] ].PreOrder == 0 ){ // jesli jeszcze nie bylem w danym wierzcholku - synu
			connectedBridgesAndArtPoints( dfsnum, nodes[myNumber][i], myNumber );
			nodes[myNumber].low = minimum( nodes[myNumber].low, nodes[ nodes[myNumber][i] ].low );
			
			if( nodes[ nodes[myNumber][i] ].low >= nodes[myNumber].PreOrder ) nodes[myNumber].isArtPoint = true;
			if( nodes[ nodes[myNumber][i] ].low == nodes[ nodes[myNumber][i] ].PreOrder ){
				ME::iterator it = edges.find( Edge( myNumber, nodes[myNumber][i] ) );
				const Edge *e = &it->ST;
				Edge *f = const_cast<Edge*>(e);
				f->isBridge = true;
			}
			
			nodes[myNumber].dfssons++;
		}
		else if( nodes[myNumber][i] != parent ){
			nodes[myNumber].low = minimum( nodes[myNumber].low, nodes[ nodes[myNumber][i] ].PreOrder );
		}
	}	
//	cout << "Wracam z wierzcholka myNumber = " << myNumber << "  mainNumber = " << nodes[myNumber].mainGraphNumber << "  low = " << nodes[myNumber].low << endl;
//	if( dfsnum == 1 ) if( nodes[myNumber].dfssons >= 2 ) nodes[myNumber].isArtPoint = true; // dla kozenia
}

void Graph::bridgesAndArtPoints(){
	REP( i,nodes.size() ) nodes[i].PreOrder = 0; // musze to wyzerowac
	
	vector<Graph> graphs = connectedComponents();
	
	cout << "Oto twoje grafy:" << endl;
	REP(i,graphs.size()){
		cout << "graph nr " << i+1 << endl;
		graphs[i].writeGraph();
	}
	
	int dfsnum;
	REP( i,graphs.size() ){
		cout << "Oto graf nr " << i+1 << endl;
		graphs[i].writeGraph();
		dfsnum = 1;
		if( graphs[i].nodes.size() >= 2 ) graphs[i].connectedBridgesAndArtPoints( dfsnum,0,-1 );	
		else graphs[i].nodes[0].isArtPoint = false;
		if( graphs[i].nodes[0].dfssons >= 2 && graphs[i].nodes.size() ) graphs[i].nodes[0].isArtPoint = true;	
		
		cout << "a teraz po connectedBridges:" << endl;
		graphs[i].writeGraph();
	}

	bool *nzmiana = new bool[nodes.size()];
	
	REP( i,nodes.size() ) nzmiana[i] = false;
	
	REP( i,graphs.size() ){
		REP(k,graphs[i].nodes.size()){
			nzmiana[ graphs[i].nodes[k].mainGraphNumber ] = graphs[i].nodes[k].isArtPoint;
		}
	}
	
	REP( i,nodes.size() ) nodes[i].isArtPoint = nzmiana[i];	
/*	cout << "JEstem po przepisaniu wierzcholkow..." << endl;  // ta wersja nie wiem dlaczego nie dzial
	REP(i,nodes.size()) cout << i << " artPoint: " << nodes[i].isArtPoint << endl;	
	bool *bzmiana = new bool[2*edges.size()];
	REP(i,2*edges.size()) bzmiana[i] = false;
	REP(i,graphs.size()){
		for( ME::iterator it = graphs[i].edges.begin(); it!=graphs[i].edges.end(); ++it ){
			bzmiana[ it->ST.mainGraphNumber ] = it->ST.isBridge;
		}
	}	
	for( ME::iterator it = edges.begin(); it!=edges.end();  it++ ){
		const Edge *e = &it->ST;
		Edge *f = const_cast<Edge*>(e);
		f->isBridge = bzmiana[ it->ST.mainGraphNumber ];
	}*/	
	
	for( ME::iterator it = edges.begin(); it!=edges.end();  it++ ){
		const Edge *e = &it->ST;
		Edge *f = const_cast<Edge*>(e);
		f->isBridge = false;
	}
	
	REP( i,nodes.size() ){ // to jest wersja dluzsza ( MlogM ), ale przynajmniej dzial :)
		REP( k,nodes[i].size() ){
			if( ( nodes[i].isArtPoint && nodes[ nodes[i][k] ].isArtPoint ) || ( nodes[i].isArtPoint && nodes[ nodes[i][k] ].size()==1 ) || 
				( nodes[i].size()==1 && nodes[ nodes[i][k] ].isArtPoint ) || ( nodes[i].size()==1 && nodes[ nodes[i][k] ].size()==1 ) ){
					const Edge *e = &edges.find( Edge( i,nodes[i][k] ) )->ST;
					Edge *f = const_cast<Edge*>(e);
					f->isBridge = true;
				}
		}
	}	
//	writeGraph();
//	cout << "JEstem po przepisaniu krawedzi" << endl;
}
