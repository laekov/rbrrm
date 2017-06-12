/* Data structure to store answers
 * Based on std::vector
 */
#ifndef LINEARR_HH
#define LINEARR_HH

#include <vector>

typedef std::vector<std::pair<int, int> > LineArr;

#define POSMK(_x_,_y_) (((_x_)<<16)|(_y_))
#define POSX(_x_) ((_x_)>>16)
#define POSY(_x_) ((_x_)&0xffff)
#define LINEMK(_x_,_y_) (std::pair<int,int>((_x_),(_y_)))

#endif // LINEARR_HH
