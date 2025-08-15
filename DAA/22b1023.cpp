#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class Point {
 public:
  long double x;
  long double y;

 public:
  Point()
      : x(0), y(0) {}  // Default constructor initializing coordinates to (0,0)
  Point(long double xVal, long double yVal)
      : x(xVal), y(yVal) {}  // Parameterized constructor

  long double X() const { return x; }  // Accessor for x coordinate
  long double Y() const { return y; }  // Accessor for y coordinate

};


long double base1(pair<Point, Point> trap){
	long double a = trap.first.X();
	long double b = trap.first.Y();
	long double c = trap.second.X();
	long double d = trap.second.Y();
	return (b+d)*(c-a)*0.5;
}

void trap_printer(pair<Point, Point> trap){
    cout<<trap.first.X()<<" "<<trap.first.Y()<<" "<<trap.second.X()<<" "<<trap.second.Y()<<"\n";
    return;
}
vector<pair<Point,Point>> base2(pair<Point, Point> trap1 , pair<Point, Point> trap2){
    
    if(trap1.first.X() > trap2.first.X()){
        pair<Point,Point> temp = trap2;
        trap2 = trap1;
        trap1 = temp;
    }
	long double a1 = trap1.first.X();
	long double b1 = trap1.first.Y();
	long double c1 = trap1.second.X();
	long double d1 = trap1.second.Y();

	long double a2 = trap2.first.X();
	long double b2 = trap2.first.Y();
	long double c2 = trap2.second.X();
	long double d2 = trap2.second.Y(); 
	//assuming the trap are passed such that a of trap1 is less than a of trap2
    vector<pair<Point,Point>> ans;
	if(a2 > c1){
        ans.push_back(trap1);
        ans.push_back(trap2);
        return ans;
	}

    if(a1 == c1){
       if(a2 == c2){
          ans.push_back({Point(a1,0) , Point(c1,0)});
          return ans;
       }
       else{
          ans.push_back(trap2);
          return ans;
       }
    }
    else if(a2 == c2){
        ans.push_back(trap1);
        return ans;
    }
	long double numerator = ((a2*d2 - b2*c2)/(a2-c2) - ((d1*a1 - b1*c1)/(a1-c1)));
    long double denominator = ((b1 - d1) / (a1 - c1)) - ((b2 - d2) / (a2 - c2));
	long double cross = -1;
	if(denominator != 0){
		cross = numerator/denominator;
	}
	long double cross_height = d2 + (cross-c2)*(b2-d2)/(a2-c2);
	long double a2_with_l1 = d1 + (a2-c1)*(b1-d1)/(a1-c1);
	long double c2_with_l1 = d1 + (c2-c1)*(b1-d1)/(a1-c1);
	long double c1_with_l2 = d2 + (c1-c2)*(b2-d2)/(a2-c2);
	
    // cout<<"Cross : "<<cross<<"\n";
    // cout<<a1<<" "<<b1<<" "<<c1<<" "<<d1<<"\n";
    // cout<<a2<<" "<<b2<<" "<<c2<<" "<<d2<<"\n";

	if(b1 >= d1){
        
        if(b2 >= d2){
            
            if(c2 >=c1){
                
               if(b2 <= a2_with_l1){
                  if(cross== -1 || cross >= c1 || cross <=a2){
                       ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,a2_with_l1),Point(c1,d1)});
                        ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                        return ans;
                  }
                  else{
                      ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                       ans.push_back({Point(a2,a2_with_l1),Point(cross,cross_height)});
                       ans.push_back({Point(cross,cross_height),Point(c1,c1_with_l2)});
                       ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                       return ans;
                  }   
			   }
			   else{
				  if(cross == -1 || cross < a2 || cross > c1){
                     ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                     ans.push_back({Point(a2,b2),Point(c1,c1_with_l2)});
                     ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                     return ans;
				  }
				  else{
                    // irrelevent
                     ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                     ans.push_back({Point(a2,b2),Point(cross,cross_height)});
                     ans.push_back({Point(cross,cross_height),Point(c1,d1)});
                     ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                     return ans;
				  }
			   }
			}
			else{
                
                if(b2 <= a2_with_l1){
                  if(cross== -1 || cross >= c2 || cross <= a2){    
                        ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,a2_with_l1),Point(c2,c2_with_l1)});
                        ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                        return ans;
                    }
                  else{
                      ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                       ans.push_back({Point(a2,a2_with_l1),Point(cross,cross_height)});
                       ans.push_back({Point(cross,cross_height),Point(c2,d2)});
                       ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                       return ans;
                  }
			   }
			   else{
				  if(cross == -1 || cross < a2 || cross > c2){
                    ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                    ans.push_back({Point(a2,b2),Point(c2,d2)});
                    ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                    return ans;
				  }
				  else{
					ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                    ans.push_back({Point(a2,b2),Point(cross,cross_height)});
                    ans.push_back({Point(cross,cross_height),Point(c2,c2_with_l1)});
                    ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                     return ans;
				  }
			   }
			}
		}

		else{
            if(c2>=c1){
                if(b2 >= a2_with_l1){
					ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                    ans.push_back({Point(a2,b2),Point(c1,c1_with_l2)});
                    ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                    return ans;
				}
				else{
					if(cross > c1 || cross == -1 || cross < a2){
						ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,a2_with_l1),Point(c1,d1)});
                        ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                        return ans;
					}
					else{
                        ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,a2_with_l1),Point(cross,cross_height)});
                        ans.push_back({Point(cross,cross_height),Point(c1,c1_with_l2)});
                        ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                        return ans;
					}
				}
			}
			else{
				 if(b2 >= a2_with_l1){
					ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                    ans.push_back({Point(a2,b2),Point(c2,d2)});
                    ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                    return ans;
				}
				else{
					if(cross > c2 || cross == -1 || cross < a2){
                        ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,a2_with_l1),Point(c2,c2_with_l1)});
                        ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                        return ans;
					}
					else{
						ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,a2_with_l1),Point(cross,cross_height)});
                        ans.push_back({Point(cross,cross_height),Point(c2,d2)});
                        ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                        return ans;
					}
				}
			}
		}
	}

	else{
		if(b2 >= d2){
            if(c2>=c1){
                 if(b2 <= a2_with_l1){
				  ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                  ans.push_back({Point(a2,a2_with_l1),Point(c1,d1)});
                  ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                  return ans;
			   }
			   else{
				  if(cross > c1 || cross == -1 || cross < a2){
					 ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                     ans.push_back({Point(a2,b2),Point(c1,c1_with_l2)});
                     ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                     return ans;
				  }
				  else{
					 ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                     ans.push_back({Point(a2,b2),Point(cross,cross_height)});
                     ans.push_back({Point(cross,cross_height),Point(c1,d1)});
                     ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                     return ans;
				  }
			   }
			}
			else{
                if(b2 <= a2_with_l1){
                  ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                  ans.push_back({Point(a2,a2_with_l1),Point(c2,c2_with_l1)});
                  ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                  return ans;
			   }
			   else{
				  if(cross > c2 || cross == -1 || cross < a2){
					ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                    ans.push_back({Point(a2,b2),Point(c2,d2)});
                    ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                    return ans;
				  }
				  else{
					ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                    ans.push_back({Point(a2,b2),Point(cross,cross_height)});
                    ans.push_back({Point(cross,cross_height),Point(c2,c2_with_l1)});
                    ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                     return ans;
				  }
			   }
			}
		}
		else{
            if(c2>=c1){
                 if(b2 >= a2_with_l1){
                    if(cross == -1 || cross > c1 || cross < a2){
                        ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,b2),Point(c1,c1_with_l2)});
                        ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                        return ans;
                    }
                    else{
                          ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                           ans.push_back({Point(a2,b2),Point(cross,cross_height)});
                           ans.push_back({Point(cross,cross_height),Point(c1,d1)});
                           ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                          return ans;
                    }
					
				}
				else{
					if(cross == -1 || cross < a2 || cross > c1){
						ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,a2_with_l1),Point(c1,d1)});
                        ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                        return ans;
					}
					else{
                        ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,a2_with_l1),Point(cross,cross_height)});
                        ans.push_back({Point(cross,cross_height),Point(c1,c1_with_l2)});
                        ans.push_back({Point(c1,c1_with_l2),Point(c2,d2)});
                        return ans;
					}
				}
			}
			else{
				 if(b2 >= a2_with_l1){
                   // cout<<"hey\n";
                    if(cross == -1 || cross > c2 || cross < a2){
                        ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,b2),Point(c2,d2)});
                        ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                        return ans;
                    }
                    else{
                          ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                           ans.push_back({Point(a2,b2),Point(cross,cross_height)});
                           ans.push_back({Point(cross,cross_height),Point(c2,c2_with_l1)});
                           ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                          return ans;
                    }
				}
				else{
                    //cout<<"ohno\n";
					if(cross == -1 || cross < a2 || cross > c2){
                        ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,a2_with_l1),Point(c2,c2_with_l1)});
                        ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                        return ans;
					}
					else{
						ans.push_back({Point(a1,b1),Point(a2,a2_with_l1)});
                        ans.push_back({Point(a2,a2_with_l1),Point(cross,cross_height)});
                        ans.push_back({Point(cross,cross_height),Point(c2,d2)});
                        ans.push_back({Point(c2,c2_with_l1),Point(c1,d1)});
                        return ans;
					}
				}
			}
		}

	}
   return ans;
}


vector<pair<Point,Point>> merge(vector<pair<Point,Point>> &ans1 , vector<pair<Point,Point>> &ans2){
    //we have outline 1 and outline 2
    vector<pair<Point,Point>> ans;
    int i=0 ;
    int j=0;
    int s1 = ans1.size();
    int s2 = ans2.size();
    vector<pair<Point,Point>> temp;
    pair<Point,Point> rem, rem2;
    int next;
    int baton;
        
    while(ans1[i].second.X() <= ans2[j].first.X() && i<s1){
        ans.push_back(ans1[i]);
        i++;
    }
    if(i == s1){
        for(int k=0 ; k<s2 ; k++){
            ans.push_back(ans2[k]);
        }
        return ans;
    }
        temp = base2(ans1[i],ans2[j]);
        for(int k=0 ; k<temp.size()-1 ; k++){
            if(fabs(temp[k].first.X() - temp[k].second.X()) > 0.0000001 || fabs(temp[k].first.Y() - temp[k].second.Y()) > 0.0000001)
            ans.push_back(temp[k]);
        }
        rem = temp[temp.size()-1];
        if(ans1[i].second.X() <= ans2[j].second.X()){
            i++;
            next = i;
            baton = 1;
        }
        else{
            j++;
            next = j;
            baton = 2;
        }
    int boolean = 0;
    while(i<s1 && j<s2){
        boolean = 1;
        pair<Point,Point> curr;
        if(baton == 1){
           curr = ans1[next];
        }
        else if(baton == 2){
            curr = ans2[next];
        }
           temp = base2(curr,rem);
           for(int k=0 ; k<temp.size()-1 ; k++){
            // cout<<"Adding to ans :  ";
            // trap_printer(temp[k]);
            // cout<<endl;
            if(fabs(temp[k].first.X() - temp[k].second.X()) > 0.0000001 || fabs(temp[k].first.Y() - temp[k].second.Y()) > 0.0000001){
                ans.push_back(temp[k]);
            }
           }
           rem2 = temp[temp.size()-1];
            // cout<<"REmaininf trap :  ";
            // trap_printer(rem2);
            // cout<<endl;
           if(curr.second.X() <= rem.second.X()){
                if(baton == 1){
                    i++;
                }
                if(baton == 2){
                    j++;
                }
                next++;
            }
            else{
                if(baton == 2){
                    baton = 1;
                    i++;
                    next = i;
                }
                else if(baton == 1){
                    baton = 2;
                    j++;
                    next = j;
                }
            }
            rem = rem2;
    }
    if(boolean == 0){
        if(fabs(rem.first.X() - rem.second.X()) > 0.0000001 || fabs(rem.first.Y() - rem.second.Y()) > 0.0000001)
        ans.push_back(rem);
    }
    else{
    if(fabs(rem2.first.X() - rem2.second.X()) > 0.0000001 || fabs(rem2.first.Y() - rem2.second.Y()) > 0.0000001)
        ans.push_back(rem2);
    }
    i++;
    j++;

    while(i<s1){
       // trap_printer(ans1[i]);
       if(fabs(ans1[i].first.X() - ans1[i].second.X()) > 0.0000001 || fabs(ans1[i].first.Y() - ans1[i].second.Y()) > 0.0000001)
        ans.push_back(ans1[i]);
        i++;
    }
    while(j<s2){
        //trap_printer(ans2[j]);
        if(fabs(ans2[j].first.X() - ans2[j].second.X()) > 0.0000001 || fabs(ans2[j].first.Y() - ans2[j].second.Y()) > 0.0000001)
        ans.push_back(ans2[j]);
        j++;
    }
    return ans;
}
vector<pair<Point,Point>> mergesort(vector<pair<Point, Point>> &posters , int l , int r , vector<pair<Point,Point>>&ans ){
	if(r-l < 0){
		return ans;
	}
	if(r-l == 0){
        ans.push_back(posters[l]);
        return ans;
	}
    if(r-l == 1){
        ans = base2(posters[l],posters[r]);
        vector<pair<Point,Point>> temp;
        for(int i=0 ; i<ans.size() ; i++){
            if(fabs(ans[i].first.X() - ans[i].second.X()) > 0.0000001 || fabs(ans[i].first.Y() - ans[i].second.Y()) > 0.0000001)
                temp.push_back(ans[i]);
        }
        ans = temp;
        return ans;
    }
	
	int mid = l + (r-l)/2;
	vector<pair<Point,Point>> ans1;
    mergesort(posters , l , mid , ans1);
	vector<pair<Point,Point>> ans2;
    mergesort(posters , mid+1 ,r ,  ans2 );
	ans = merge(ans1 , ans2);

	return ans;
}

bool comparePosters(const pair<Point, Point>& poster1, const pair<Point, Point>& poster2) {
    return poster1.first.X() < poster2.first.X();
}

int main(){
	   /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
	int n;
	cin >> n;
	int a,b,c,d;

	vector <pair<Point, Point> > posters; 

	for(int i=0; i<n; i++){
		cin >> a;
		cin >> b;
		cin >> c;
		cin >> d;

		posters.push_back(make_pair(Point(a,b), Point(c,d)));	
	}
    
    //sort(posters.begin() , posters.end() , comparePosters);

    // for(int i=0 ; i<posters.size() ; i++){
    //     trap_printer(posters[i]);
    // }
    
	vector<pair<Point,Point>> vec;
    
    long double area = 0;
    int lengthCovered = 0;
    
    mergesort(posters , 0 , posters.size()-1 , vec);

    // for(auto e : vec){
    //     trap_printer(e);
    // }
    for(int i=0 ; i<vec.size() ; i++){
        // if(fabs(vec[i].second.Y()) > 0.0000001 || fabs(vec[i].first.Y()) > 0.0000001)
        //lengthCovered += vec[i].second.X() - vec[i].first.X();
        if(fabs(vec[i+1].first.X() - vec[i].second.X() > 0.000001))
            lengthCovered += vec[i+1].first.X() - vec[i].second.X();
        area += base1(vec[i]);
    }
	// int lengthCovered = 0;
	lengthCovered = vec[vec.size()-1].second.X() - vec[0].first.X() - lengthCovered;
	cout << static_cast<int>(lengthCovered)<< endl;
	
	cout << static_cast<int>(area) << endl;

	return 0;
}
