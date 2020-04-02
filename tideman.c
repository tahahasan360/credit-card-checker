#include <cs50.h>
#include <stdio.h>
#include <string.h>

//max number of candidates
#define MAX 9

//losers(i) gives the number of candidates that lose to i
int losers(int i);

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair sortedpairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int voter_count;
int cycle_counter;
int x = 0;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int i);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(candidates[k], name) == 0)
        {
            ranks[rank] = k;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int j = 0; j < candidate_count; j++)
    {
        for (int k = 0; k < candidate_count; k++)
        {
            if (j < k)
            {
                preferences[ranks[j]][ranks[k]] ++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int sortcounter = 0;
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] == voter_count - i)
            {
                sortedpairs[sortcounter].winner = pairs[j].winner;
                sortedpairs[sortcounter].loser = pairs[j].loser;
                //printf("%s%s ", candidates[sortedpairs[sortcounter].winner], candidates[sortedpairs[sortcounter].loser]);
                sortcounter ++;
            }
            if (sortcounter == pair_count)
            {
                for (int k = 0; k < pair_count; k++)
                {
                    pairs[k].winner = sortedpairs[k].winner;
                    pairs[k].loser = sortedpairs[k].loser;
                    printf("%s%s ", candidates[pairs[k].winner], candidates[pairs[k].loser]);
                }
                return;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        cycle_counter = pairs[i].winner;
        if (cycle(pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
            //printf("#");
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        x = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                x++;
            }
        }
        if (x == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

//Return true if locking in creates a cycle
//defined recursively
bool cycle(int a)
{
    if (losers(a) == 0)
    {
        return false;
    }
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[a][j] == true)
        {
            int k = j;
            if (k == cycle_counter)
            {
                a = cycle_counter;
                return true;
            }
            else if (cycle(k) == true)
            {
                return true;
            }
        }
    }
    a = cycle_counter;
    return false;
}

//Give the number of candidates who lose when paired with i
int losers(int i)
{
    int y = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (preferences[i][j] > 0.5 * voter_count)
        {
            y++;
        }
    }
    return y;
}
