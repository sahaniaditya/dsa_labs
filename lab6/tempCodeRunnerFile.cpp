for(auto& it : index_entry){
        //cout << it.getWord() << endl;
        cout << it.getWord() << " " << it.getWord().size() << endl;
        vector<pair<string,int>> vec = it.getChapterWordCounts();
        for(auto it : vec){
            cout << it.first << " " << it.second << endl;
        }
    }