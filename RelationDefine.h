#ifndef __RELATIONDEFINE_H__

#define rel_length 16

#define relation_SimlTr relation[0]
#define relation_SimlAc relation[1]
#define relation_SimlPr relation[2]
#define relation_ContPs relation[3]
#define relation_ExplDepe relation[4]
#define relation_ImplDepe relation[5]
#define relation_NegiAc relation[6]
#define relation_TrigEve relation[7]
#define relation_PeerAuth relation[8]
#define relation_LeapAuth relation[9]
#define relation_CompAuth relation[10]
#define relation_contrary_ExplDepe relation[11]
#define relation_contrary_ImplDepe relation[12]

#define _SimlTr [0]
#define _SimlAc [1]
#define _SimlPr [2]
#define _ContPs [3]
#define _ExplDepe [4]
#define _ImplDepe [5]
#define _NegiAc [6]
#define _TrigEve [7]
#define _PeerAuth [8]
#define _LeapAuth [9]
#define _CompAuth [10]
#define _contrary_ExplDepe [11]
#define _contrary_ImplDepe [12]

#define NO_Conflict 0
#define Shadow_Conflict 1
#define Execution_Conflict 2
#define Environment_Mutual_Conflict 3
#define Direct_Dependence_Conflict 4
#define Indirect_Dependence_Conflict 5

#endif /*__RELATIONDEFINE_H__*/