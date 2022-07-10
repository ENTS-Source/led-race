import * as React from "react";
import { TopScores } from "../TopScores";
import { LastGame } from "../LastGame";

import "./Main.css";

export function Main() {
    return <>
        <h1 className='fd_title fd_titleText'>Formula Diode</h1>
        <TopScores />
        <LastGame />
    </>;
}
