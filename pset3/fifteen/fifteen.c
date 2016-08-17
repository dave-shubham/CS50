/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

struct ij
{
    int i,j;
};

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
struct ij find_tile(int tile);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();
    int i,j;
    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (i = 0; i < d; i++)
        {
            for (j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            usleep(500000);
            draw();
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 or greater than d*d-1 (for testing)
        if (tile == 0 || tile >d*d-1)
        {
//            printf("\nIllegal move.\n");
//            usleep(500000);
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }
        else
        {
           struct ij pair=find_tile(0),pair2=find_tile(tile);
           board[pair.i][pair.j]=board[pair.i][pair.j]^board[pair2.i][pair2.j];
           board[pair2.i][pair2.j]=board[pair.i][pair.j]^board[pair2.i][pair2.j];
           board[pair.i][pair.j]=board[pair.i][pair.j]^board[pair2.i][pair2.j];
           //printf("%d\t%d\t%d\t%d\n",pair.i,pair.j,pair2.i,pair2.j);
           //printf("Tile moved\n");
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int i,j,count=(d*d) - 1;
    // TODO
    for(i=0;i<d;i++)
        {
            for(j=0;j<d;j++)
            {
                board[i][j]=count;
                count--;
            }
        }
    if(d%2 == 0)
    {
        board[d-1][d-3]=board[d-1][d-3]^board[d-1][d-2];
        board[d-1][d-2]=board[d-1][d-3]^board[d-1][d-2];
        board[d-1][d-3]=board[d-1][d-3]^board[d-1][d-2];
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    int i,j;
    for(i=0;i<d;i++)
    {
        for(j=0;j<d;j++)
        {
            printf("%d\t",board[i][j]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    int i,j;
    struct ij pair=find_tile(0);
    i=pair.i;
    j=pair.j;
//    printf("%d\t%d\n",i,j);

    if( (i==0 && (j==0 || j==d-1) ) || (i==d-1 && (j==0 || j==d-1) ) )
    {
        //printf("Extreme Corner\n");
        if(i==0 && j == 0)
        {
            if(board[i+1][j]==tile || board[i][j+1]==tile)
            {
                return true;
            }
        }
        else if(i==0 && j == d-1)
        {
            if(board[i+1][j]==tile || board[i][j-1]==tile)
            {
                return true;
            }
        }
        else if(i==d-1 && j == d-1)
        {
            if(board[i-1][j]==tile || board[i][j-1]==tile)
            {
                return true;
            }
        }
        else if(i==d-1 && j == 0)
        {
            if(board[i][j+1]==tile || board[i-1][j]==tile)
            {
                return true;
            }
        }
    }
    else if( i!=0 && i!=d-1 && j!=0 && j!=d-1)
    {
        //printf("Inner Square\n");
        if(board[i+1][j]==tile || board[i][j+1]==tile || board[i][j-1]==tile || board[i-1][j]==tile)
        {
            return true;
        }
    }
    else
    {
        //printf("Corner Wall\n");
        if(i==0)
        {
            if(board[i+1][j]==tile || board[i][j+1]==tile || board[i][j-1]==tile)
            {
                return true;
            }
        }
        else if(i==d-1)
        {
            if(board[i-1][j]==tile || board[i][j+1]==tile || board[i][j-1]==tile)
            {
                return true;
            }
        }
        else if(j == d-1)
        {
            if(board[i+1][j]==tile || board[i-1][j]==tile || board[i][j-1]==tile)
            {
                return true;
            }
        }
        else if(j == 0)
        {
            if(board[i+1][j]==tile || board[i-1][j]==tile || board[i][j+1]==tile)
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    int i,j,count=1;
    for(i=0;i<d;i++)
    {
        for(j=0;j<d;j++)
        {
            if(i==d-1 && j==d-1)
            {
                if(board[i][j]!=0)
                {
//                    printf("Err!");
                    return false;
                }
            }
            else
            {
                if(board[i][j]!=count)  
                {
//                    printf("Err!");
                    return false;
                }
            }
            count++;
        }
    }
    return true;
}

struct ij find_tile(int tile)
{
    bool tile_found=false;
    int i,j;
    for(i=0;i<d;i++)
    {
        for(j=0;j<d;j++)
        {
            if(board[i][j]==tile)
            {
                tile_found=true;
                break;
            }
        }
        if(tile_found==true)
        {
            break;
        }
    }
    struct ij pair;
    pair.i=i;
    pair.j=j;
    return(pair);
}