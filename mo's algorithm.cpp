//USE int64_t ALWAYS
//implement insert,remove and calc function
//rest is taken care of 
//pass in constructor true/false for update
//update and rollback function are assignment
class Mo{
	private:
	int blk;
	class Query{
		public:
		mutable int l,r,id,od,lb,rb;
		private:
		const int rot_delta[4]={3,0,0,1};
		int hilbert_curve(int u,int v,int pw,int rot){
			if(pw==0)
				return 0;
			int hp= 1LL<<(pw-1LL);
			int p=(u<hp?(v<hp?0:3):(v<hp?1:2));
			p=(p+rot) & 3;
			u&=(u^hp);
			v&=(v^hp);
			rot=(rot + rot_delta[p]) & 3;
			int sbsq= 1LL<<(2LL*pw -2LL);
			int ord=p*sbsq;
			int add=hilbert_curve(u,v,pw-1,rot);
			ord+=(p==1||p==2)?add:(sbsq-add-1);
			return ord;
		}
		public:
		Query(){}
		Query(int _l,int _r,int _id){
			l=_l;
			r=_r;
			id=_id;
			lb=l/blk;
			rb=r/blk;
			od=hilbert_curve(l,r,21,0);
		}
		void operator =(Query qq)const{
			l=qq.l;
			r=qq.r;
			id=qq.id;
			od=qq.od;
			lb=qq.lb;
			rb=qq.rb;
		}
		//without Update
		bool operator < (Query qq) const
		{ return od<qq.od; }
		//with Update
		bool operator < (Query qq) const
		{ return lb!=qq.lb?l<qq.l:(rb!=qq.rb?r<qq.r:tim<qq.tim); }
	};
	class Update{
		public:
		mutable int id,z,old;
		Update(){}
		Update(int _id, int _z){
			id=_id;
			z=_z;
		}
		void operator =(Update up) const{
			id=up.id;
			z=up.z;
			old=up.old;
		}
	};
	vector<Query> qry;
	vector<Update> upd;
	int time;
	bool chg;
	public:
	vector<int> ans;
	Mo(bool _chg){
		chg=_chg;
		time=0;
		blk=chg?cbrt(n):1;
		blk*=blk;
		upd.push_back(Update(MAX-1,0));
	}
	void add_query(int l,int r,int id){
		qry.push_back(Query(l,r,id));
		ans.push_back(0);
	}
	void add_update(int id, int z){
		time++;
		ans.push_back(-1);
		upd.push_back(Update(id,z));
	}
	void insert(int u){
		//insert index u to active range
	}
	void remove(int u){
		//remove index u from active range
	}
	void update(int id,int l,int r){
		int i=upd[id].id;
		upd[id].old=a[i];
		if(l<=i && i<=r)
			remove(i);
		a[i]=upd[id].z;
		if(l<=i && i<=r)
			insert(i);
		return;
	}
	void rollback(int id,int l,int r){
		int i=upd[id].id;
		if(l<=i && i<=r)
			remove(i);
		a[i]=upd[id].old;
		if(l<=i && i<=r)
			insert(i);
		return;
	}
	int calc(){
		//calculate ans for current range 
		return ;
	}
	void solve(){
		sort(qry.begin(),qry.end());
		int l=0,r=-1,cur_tim=0;
		for(auto q:qry){
			if(chg){
				while(cur_tim<q.tim)update(++cur_tim,l,r);
				while(cur_tim>q.tim)rollback(cur_tim--,l,r);
			}
			while(r<q.r)insert(++r);
			while(r>q.r)remove(r--);
			while(l<q.l)remove(l++);
			while(l>q.l)insert(--l);
			ans[q.id]=calc();
		}
	}
};