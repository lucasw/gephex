# pong module, play pong

mod_pongmodule
{
    name          = Pong Game
    deterministic = true
    group         = Games
    xpm           = pongmodule.xpm
    author        = martin
    version       = 0.1pregamersrelease
}

inputs
{
    p1
    {
        name              = Player1Position
        type              = typ_NumberType
        const             = true
	strong_dependency  = true
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0.5
    }

    p2
    {
        name              = Player2Position
        type              = typ_NumberType
        const             = true
	strong_dependency  = true
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0.5
    }

    ball_x
    {
        name              = BallX
        type              = typ_NumberType
        const             = true
	strong_dependency = true
        default           = 0.01
    }

    ball_y
    {
        name              = BallY
        type              = typ_NumberType
        const             = true
	strong_dependency = true
        default           = 0.01
    }


    speed_x
    {
        name              = SpeedX
        type              = typ_NumberType
        const             = true
	strong_dependency = true
        default           = 0.01
    }

    speed_y
    {
        name              = SpeedY
        type              = typ_NumberType
        const             = true
	strong_dependency = true
        default           = 0.01
    }

    start
    {
        name              = Start
        type              = typ_NumberType
        const             = true
	strong_dependency = true
        widget_type       = radio_button
        true_value        = 1
        false_value       = 0
        default           = 1
    }
}

outputs
{
    screen
    {
        name = Videoout
        type = typ_FrameBufferType
    }

    speed_x
    {
        name              = SpeedX
        type              = typ_NumberType
    }

    speed_y
    {
        name              = SpeedY
        type              = typ_NumberType
    }


    ball_x
    {
        name              = BallX
        type              = typ_NumberType
    }

    ball_y
    {
        name              = BallY
        type              = typ_NumberType
    }

    status
    {
        name              = RightPad
        type              = typ_NumberType
    }
}
