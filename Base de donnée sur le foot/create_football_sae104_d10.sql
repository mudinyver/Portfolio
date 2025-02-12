//LEFRANÇOIS Julien et UDIN--YVER Mael, groupe d10

VAR club REAL RELATION{
    club_id INT,
    club_name CHAR,
    club_acronym CHAR
}KEY{club_id};

VAR team REAL RELATION{
    team_id INT,
    team_name CHAR,
    coach_name_firstname CHAR,
    club_id INT
}KEY{team_id};
CONSTRAINT team_fk1 team{club_id} = club{club_id};

VAR season REAL RELATION{
    season_id CHAR
}KEY{season_id};

VAR day REAL RELATION{
    season_id CHAR,
    day_nr INT
}KEY{season_id,day_nr};

CONSTRAINT day_fk1_season day{season_id} <= season{season_id};

VAR match REAL RELATION{
    local_id INT,
    visitor_id INT,
    season_id CHAR,
    day_nr INT,
    attendance INT,
    local_goals INT,
    visitor_goals INT,
    match_date_time CHAR
}KEY{local_id,visitor_id,season_id,day_nr};

CONSTRAINT match_fk1 match{local_id} <= (team RENAME{team_id as local_id}){local_id};
CONSTRAINT match_fk2 match{visitor_id} <= (team RENAME{team_id as visitor_id}){visitor_id};
CONSTRAINT match_fk3 match{season_id} <= day{season_id};
CONSTRAINT match_fk4 match{day_nr} <= day{day_nr};

VAR league REAL RELATION{
    league_id INT,
    league_name CHAR
}KEY{league_id};

VAR date REAL RELATION{
    date CHAR
}KEY{date};

VAR player REAL RELATION{
    player_id INT,
    player_name CHAR,
    player_firstname CHAR,
    date_of_birth CHAR,
    nationality CHAR,
    birth_country CHAR,
    weight RATIONAL,
    size RATIONAL
}KEY{player_id};

VAR takes_part REAL RELATION{
    season_id CHAR,
    team_id INT,
    league_id INT
}KEY{season_id,team_id,league_id};
CONSTRAINT takes_part_fk1 takes_part{season_id} <= season{season_id};
CONSTRAINT takes_part_fk2 takes_part{team_id} <= team{team_id};
CONSTRAINT takes_part_fk3 takes_part{league_id} <= league{league_id};

VAR characteristics REAL RELATION {
    league_id INT,
    season_id CHAR,
    day_nr INT,
    number_of_teams INT
}KEY{season_id,day_nr,league_id};
CONSTRAINT characteristics_fk1 characteristics{season_id} <= day{season_id};
CONSTRAINT characteristics_fk2 characteristics{day_nr} <= day{day_nr};
CONSTRAINT characteristics_fk3 characteristics{league_id} <= league{league_id};

VAR belongs_to REAL RELATION {
    club_id INT,
    league_id INT}KEY
{club_id,league_id};
CONSTRAINT belongs_to_fk1 belongs_to{club_id} = club{club_id};
CONSTRAINT belongs_to_fk2 belongs_to{league_id} <= league{league_id};

VAR fin REAL RELATION{
    team_id INT,
    date CHAR,
    player_id INT
}KEY{team_id, date, player_id};
CONSTRAINT fin_fk1 fin{team_id} <= team{team_id};
CONSTRAINT fin_fk2 fin{date} <= date{date};
CONSTRAINT fin_fk3 fin {player_id} <= player{player_id};

VAR start REAL RELATION{
    team_id INT,
    date CHAR,
    player_id INT
}KEY{team_id, date, player_id};
CONSTRAINT start_fk1 start{team_id} <= team{team_id};
CONSTRAINT start_fk2 start{date} <= date{date};
CONSTRAINT start_fk3 start{player_id} <= player{player_id};

VAR plays REAL RELATION{
    player_id INT,
    day_nr INT,
    season_id CHAR,
    position CHAR,
    starting_time INT,
    yellow_cards INT,
    red_card BOOL,
    shirt_nr INT
}KEY{player_id, day_nr};
CONSTRAINT plays_fk1 plays{player_id} <= player{player_id};
CONSTRAINT plays_fk2 plays{day_nr} <= day{day_nr};
CONSTRAINT plays_fk3 plays{season_id} <= day{season_id};
