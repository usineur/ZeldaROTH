/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Lang.h"
#include "Texte.h"
#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"

Texte::Texte(Jeu* jeu) : gpJeu(jeu), vitesse(40), av(0), x(0), y(0), w(0), h(0),
id(0), idsuiv(0), def(false), cadre(false), texte(""), buffer("") {
    lastAnimTime = SDL_GetTicks();
    imageFont = gpJeu->loadImg("data/images/texte/font.png");
    SDL_SetColorKey(imageFont,SDL_SRCCOLORKEY,SDL_MapRGB(imageFont->format,0,0,255));
#ifdef __vita__
    imageButtons = gpJeu->loadImg("data/images/texte/buttons.png");
    SDL_SetColorKey(imageButtons,SDL_SRCCOLORKEY,SDL_MapRGB(imageFont->format,0,0,255));
#endif
    imageCoeur = gpJeu->loadImg("data/images/menu/coeur.png");
    SDL_SetColorKey(imageCoeur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCoeur->format,0,0,255));
    getTextByLangFunc = &Texte::getTexteEN;
}

Texte::~Texte() {
#ifdef __vita__
    SDL_FreeSurface(imageButtons);
#endif
    SDL_FreeSurface(imageFont);
    SDL_FreeSurface(imageCoeur);
}

void Texte::setTextLanguage(int id){
    SDL_FreeSurface(imageFont);
    switch(id){
        case LANG_FR:
            getTextByLangFunc = &Texte::getTexteFR;
            imageFont = gpJeu->loadImg("data/images/texte/font.png");
            break;
        case LANG_DE:
            getTextByLangFunc = &Texte::getTexteDE;
            imageFont = gpJeu->loadImg("data/images/texte/font.png");
            break;
        case LANG_ES:
            getTextByLangFunc = &Texte::getTexteES;
            imageFont = gpJeu->loadImg("data/images/texte/font_ES.png");
            break;
        default:
            getTextByLangFunc = &Texte::getTexteEN;
            imageFont = gpJeu->loadImg("data/images/texte/font.png");
    }

    SDL_SetColorKey(imageFont,SDL_SRCCOLORKEY,SDL_MapRGB(imageFont->format,0,0,255));
}

std::string Texte::getTexteEN(int id, std::string s){
    std::string texte = "";
    switch(id) {
        // 0 -> 99 : Carte
        case 0 : 
            texte = "Forest Temple"; 
            break;
        case 1 : 
            texte = "Water Temple"; 
            break;
        case 2 : 
            texte = "Mountain Temple";
            break;
        case 3 : 
            texte = "Desert Temple"; 
            break;
        case 4 : 
            texte = "Dark Temple"; 
            break;
        case 5 : 
            texte = "Fire Temple"; 
            break;
        case 6 : 
            texte = "Ice Temple"; 
            break;
        case 7 : 
            texte = "Hidden Temple"; 
            break;
        case 8 : 
            texte = "Hyrule Castle"; 
            break;

        // 100 -> 199 : Encyclopedie
        case 100 : 
            texte = "MONSTERS " + s;
            break;
            
        // 200 -> 299 : Generique
        case 200 :
            texte = "PLAYER SELECT";
            break;
        case 201 : 
            texte = "1.";
            break;
        case 202 :
            texte = "2.";
            break;
        case 203 : 
            texte = "3.";
            break;
        case 204 :
            texte = "OPTIONS";
            break;
        case 205 :
            texte = "RECORDS";
            break;
        case 206 :
            texte = "OPTIONS";
            break;
        case 207 :
            texte = "MUSIC";
            break;
        case 208 :
            texte = "SOUND";
            break;
        case 209 :
            texte = "RETURN";
            break;
        case 210 :
            texte = "RECORDS";
            break;
        case 211 :
            texte = "BEST TIME: " + s;
            break;
        case 212 :
            texte = "100% RANK";
            break;
        case 213 :
            texte = "ULTIMATE RANK";
            break;
        case 214 :
            texte = "SPEED RANK";
            break;
        case 215 :
            texte = "RETURN";
            break;
        case 216 :
            texte = "ERASE";
            break;
        case 217 :
            texte = "ERASE ?";
            break;
        case 218 :
            texte = "YES";
            break;
        case 219 :
            texte = "NO";
            break;
        case 220 :
            texte = "LOAD";
            break;
        case 221 :
            texte = "ERASE";
            break;
        case 222 :
            texte = "CANCEL";
            break;
        case 223 :
            texte = "HELP 1/2";
            break;
        case 224 :
#ifdef __vita__
            texte = "Return to the game: ¾3 - Next: ¾5";
#else
            texte = "Return to the game: Enter - Next: Right";
#endif
            break;
        case 225 :
#ifdef __vita__
            texte = "Read / Open / Speak: ¾2";
#else
            texte = "Read / Open / Speak: Space";
#endif
            break;
        case 226 :
#ifdef __vita__
            texte = "Confirm / Pass text: ¾3";
#else
            texte = "Confirm / Pass text: Enter";
#endif
            break;
        case 227 :
#ifdef __vita__
            texte = "Move Link: Left ¾9";
#else
            texte = "Move Link: Direction Arrows";
#endif
            break;
        case 228 :
#ifdef __vita__
            texte = "Run : L (lock) / R";
#else
            texte = "Run : Shift hold or Caps lock";
#endif
            break;
        case 229 :
#ifdef __vita__
            texte = "Use sword: ¾4";
#else
            texte = "Use sword: Z or W";
#endif
            break;
        case 230 :
#ifdef __vita__
            texte = "Spin attack: Hold ¾4 then dropped";
#else
            texte = "Spin attack: Z or W hold then dropped";
#endif
            break;
        case 231 :
#ifdef __vita__
            texte = "Item selection: ¾5";
#else
            texte = "Item selection: Enter";
#endif
            break;
        case 232 :
#ifdef __vita__
            texte = "Use selected object: ¾1";
#else
            texte = "Use selected object: X";
#endif
            break;
        case 233 :
#ifdef __vita__
            texte = "Carry without select gloves: ¾3";
#else
            texte = "Carry without select gloves: C";
#endif
            break;
        case 234 :
#ifdef __vita__
            texte = "See the map: ¾7 (outside or dungeons)";
#else
            texte = "See the map: P (outside or dungeons)";
#endif
            break;
        case 235 :
#ifdef __vita__
            texte = "See the map: Left D-Pad (in dungeons)";
#else
            texte = "See the map: P (in dungeons)";
#endif
            break;
        case 236 :
#ifdef __vita__
            texte = "See defeated monsters: ¾6";
#else
            texte = "See defeated monsters: M";
#endif
            break;
        case 237 :
#ifdef __vita__
            texte = "Look around: Right ¾9";
#else
            texte = "Look around: Ctrl and direction";
#endif
            break;
        case 238 :
#ifdef __vita__
            texte = "Save / Quit: Start";
#else
            texte = "Save / Quit: Esc";
#endif
            break;
        case 239 :
#ifdef __vita__
            texte = "";
#else
            texte = "Enlarge / Shrink: Ctrl and Enter";
#endif
            break;
        case 240 :
            texte = "HELP 2/2";
            break;
        case 241 :    
#ifdef __vita__
            texte = "Return to the game: ¾3 - Previous: ¾7";
#else
            texte = "Return to the game: Enter - Previous: Left";
#endif
            break;
        case 242 :
#ifdef __vita__
            texte = "Use selected object: ¾1";
#else
            texte = "Use selected object: X";
#endif
            break;
        case 243 :
#ifdef __vita__
            texte = "Carry without select gloves: ¾3"; 
#else
            texte = "Carry without select gloves: C"; 
#endif
            break;
        case 244 :
#ifdef __vita__
            texte = "See the map: ¾7 (outside or dungeons)";
#else
            texte = "See the map: P (outside or dungeons)";
#endif
            break;
        case 245 :
#ifdef __vita__
            texte = "See the map: ¾7 (in dungeons)";
#else
            texte = "See the map: P (in dungeons)";
#endif
            break;
        case 246 :
#ifdef __vita__
            texte = "See defeated monsters: ¾6";
#else
            texte = "See defeated monsters: M";
#endif
            break;
        case 247 :
#ifdef __vita__
            texte = "Look around: Right ¾9";
#else
            texte = "Look around: Ctrl and direction";
#endif
            break;
        case 248 :
#ifdef __vita__
            texte = "Save / Quit: Start";
#else
            texte = "Save / Quit: Esc";
#endif
            break;
        case 249 :
#ifdef __vita__
            texte = "";
#else
            texte = "Enlarge / Shrink: Ctrl and Enter";
#endif
            break;

        case 250 :
            texte = "RANK: Hero of Hyrule";
            break;
        case 251 :
            texte = "RANK: UNKNOWN";
            break;
        case 252 :
            texte = "100% completion of the game";
            break;
        case 253 :
            texte = "RANK: Swanky";
            break;
        case 254 :
            texte = "RANK: UNKNOW";
            break;
        case 255 :
            texte = "Completed the game without dying,";
            break;
        case 256 :
            texte = "with 10 hearts at the very most,";
            break;
        case 257 :
            texte = "without talking to the Great Fairies,";
            break;
        case 258 :
            texte = "without buying bottles";
            break;
        case 259 :
            texte = "and without taking a shield.";
            break;
        case 260 :
            texte = "RANK: Hyrule Marathon Runner";
            break;
        case 261 :
            texte = "RANK: UNKNOW";
            break;
        case 262 :
            texte = "Complete the game in less than";
            break;
        case 263 :
            texte = "two hours";
            break;
        case 264 : 
            texte = "RESULTS:";
            break;
        case 265 :
            texte = "Game time: " + s;
            break;
        case 266 :
            texte = "Dead " + s + " time";
            break;
        case 267 :
            texte = "Dead " + s + " times";
            break;
        case 268 :
            texte = "Pieces of heart: " + s + " / 36";
            break;
        case 269 :
            texte = "Objects: " + s + " / 56";
            break;
        case 270 :
            texte = "Defeated all kinds of enemies: " + s + " / 46";
            break;
        case 271 :
            texte = "You completed the game with " + s + "%, congratulations!";
            break;
        case 272 :
            texte = "RANK: ";
            break;
        case 273 :
            texte = " - Swanky";
            break;
        case 274 :
            texte = " - Hero of Hyrule";
            break;
        case 275 :
            texte = " - Perfectionist";
            break;
        case 276 :
            texte = " - Zelda Fan";
            break;
        case 277 :
#ifdef __vita__
            texte = " - Pad professional";
#else
            texte = " - Keyboard professional";
#endif
            break;
        case 278 :
            texte = " - Experienced";
            break;
        case 279 :
            texte = " - Novice";
            break;
        case 280 :
            texte = " - Living dead";
            break;
        case 281 : 
            texte = " - Kamikaze";
            break;
        case 282 :
            texte = " - Hyrule Marathon Runner";
            break;
        case 283 :
            texte = "LANGUAGE";
            break;
        case 284 :
            texte = "English";
            break;

        // 300 -> 399 : Menu
        case 300 :
            texte = "X";
            break;
        case 301 :
            texte = "STATUS:";
            break;
        case 302 :
            texte = "LIFE      : " + s;
            break;
        case 303 :
            texte = "MAGIC     : " + s;
            break;
        case 304 :
            texte = "STRENGTH  : " + s;
            break;
        case 305 :
            texte = "DEFENSE   : " + s;
            break;
        case 306 :
            texte = "TIME      : " + s;
            break;
        case 307 :
            texte = "CRYSTALS:";
            break;

        // 500 -> ? : Texte
        case 501 : texte = "You find a shield!!!**Your defense rises by one point!"; break;
#ifdef __vita__
        case 502 : texte = "You find a sword!!!**You can now fight monsters with the key ¾4!!!*Hold ¾4 to charge a spin attack!!!"; break;
#else
        case 502 : texte = "You find a sword!!!**You can now fight monsters with the key Z (or W)!!!*Hold Z to charge a spin attack!!!"; break;
#endif
        case 503 : texte = "You find a piece of heart!!!"; break;
        case 504 : texte = "Again "+s+" before having a new heart!!!"; break;
        case 505 : texte = "Your heart count just increases!!!"; break;
        case 511 : texte = "N: Link's Home*W: Hyrule Field*E: Forest Temple"; break;
        case 512 : texte = "Mountain Temple**Not for cardiacs, scaredy-cats, and generally faint of heart."; break;
        case 513 : texte = "W: Desert entrance*N: Mountain Temple"; break;
        case 514 : texte = "N: Mountain Temple*S: Hyrule Field"; break;
        case 515 : texte = "N: Death Mountain"; break;
        case 516 : texte = "E: Forest Entrance"; break;
        case 517 : texte = "S: Lake Hylia*E: Haunted Graveyard"; break;
        case 518 : texte = "S: To Kakariko Village"; break;
        case 519 : texte = "N: Kakariko Village"; break;
        case 520 : texte = "N: Hyrule Field"; break;
        case 521 : texte = "W: Fire Land"; break;
        case 522 : texte = "E: Shadow Village*- Not for the living -"; break;
        case 523 : texte = "Dark Temple**If you are a ghost, seeking a job, you'd better come here to hang out with us."; break;
        case 524 : texte = "N: Shadow Village*W: Lake Hylia"; break;
        case 525 : texte = "N: Haunted Graveyard**No entry"; break;
        case 526 : texte = "Shadow Village"; break;
        case 527 : texte = "I am selling a bottle for 100 rupees, are you interested?*              YES ?            no  "; break;
        case 528 : texte = "I am selling a bottle for 100 rupees, are you interested?*              yes             NO ?"; break;
        case 529 : texte = "Sorry, you don't have enough rupees"; break;
        case 530 : texte = "Thank you, here is your bottle."; break;
        case 531 : texte = "Come again if you change your mind."; break;
        case 532 : texte = "Sorry, that was my only bottle."; break;
        case 533 : texte = "You find an empty bottle!!!**It will help you to stock potions!!!"; break;
        case 535 : texte = "The inhabitants of that village have a dialect out of the ordinary, I don't understand anything..."; break;
        case 536 : texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 537 : texte = "Wangle chief's permit if you really want to pass!!!"; break;
        case 538 : texte = "The chief allows you to pass??? Grrrr... So move along!!!"; break;
        case 539 : texte = "Get out of my way!!!"; break;
        case 540 : texte = "It's not common to have visitors around here."; break;
        case 541 : texte = "Local monsters don't fear a lot of things, fortunately they only attack humans."; break;
        case 542 : texte = "Really?*You understand what I say?"; break;
        case 543 : texte = "N: Desert and Gerudo Village"; break;
        case 544 : texte = "S: Lake Hylia*W: Hyrule Castle"; break;
        case 545 : texte = "Kakariko Village"; break;
        case 546 : texte = "W: Hyrule Castle"; break;
        case 547 : texte = "What a good day!!!"; break;
        case 548 : texte = "But why did I accept to take care of that rubbish???*I loathe hens!!!"; break;
        case 549 : texte = "You can find a lot of things in the shop of this village."; break;
        case 550 : texte = "S: Kakariko Village*W: Desert*E: Death Mountain"; break;
        case 551 : texte = "Gerudo Village"; break;
        case 552 : texte = "Lost in the desert?*You are here:*                        X"; break;
        case 554 : texte = "S: To Hyrule Castle"; break;
        case 555 : texte = "Desert Temple**Come to try our bath.*(water is not for drinking)"; break;
        case 556 : texte = "Forest Temple**Save the trees, eat beaver!!!"; break;
        case 557 : texte = "Lake Temple**Compulsory bathing cap."; break;
        case 558 : texte = "Ice Temple**The staff wishes to remind you that a dungeon is not a ice rink."; break;
        case 559 : texte = "Did you see the blacksmith of that village?*He is said to be very gifted to improve adventurers' equipment, a lot of people visit him."; break;
        case 560 : texte = "The Temple is in the deepest desert, in an ancient oasis."; break;
        case 561 : texte = "S: Fire Land*E: Kakariko Village"; break;
        case 562 : texte = "Hyrule Castle"; break;
        case 563 : texte = "E: Kakariko Village"; break;
        case 564 : texte = "W: Turtle Rock*E: Lake Hylia"; break;
        case 565 : texte = "Hidden Temple**Here rests the Sword of Evils Bane, the Master Sword."; break;
        case 566 : texte = "N: To the Haunted Graveyard"; break;
#ifdef __vita__
        case 567 : texte = "You find the Dungeon Map!!!*Press ¾7 to see the map."; break;
#else
        case 567 : texte = "You find the Dungeon Map!!!*Press P to see the map."; break;
#endif
        case 568 : texte = "You find the Compass!!!*You can locate the boss and chests on the plan."; break;
        case 569 : texte = "You find the Boss Key!!!"; break;
        case 570 : texte = "You find a small key!!!*Go near a door to open it."; break;
#ifdef __vita__
        case 571 : texte = "You find the Gloves!!!*Use them to lift some object setting them up or pressing ¾3."; break;
#else        
        case 571 : texte = "You find the Gloves!!!*Use them to lift some object setting them up or pressing C."; break;
#endif
        case 572 : texte = "You find a Magic Crystal!!!"; break;
        case 573 : texte = "For what may it be used...?"; break;
        case 574 : texte = "There are "+s+" left to find!!!"; break;
        case 575 : texte = "Only 2 left to find!!!"; break;
        case 576 : texte = "You lack only one!!!"; break;
        case 577 : texte = "You have all the crystals, run to the castle and save Zelda!!!"; break;
        case 580 : texte = "You find the Hookshot!!!*Use it to overcome obstacles."; break;
        case 581 : texte = "You find the Lantern!!!*Use it to shut up flames."; break;
        case 582 : texte = "You find the Flippers!!!*Set them up to go in the water."; break;
        case 583 : texte = "You find the Magic Hammer!!!*Use it to squash obstacles."; break;
        case 584 : texte = "You find the Fire Rod!!!*From now on you are able to shoot out powerful flames."; break;
        case 585 : texte = "You find the Ice Rod!!!*Use it to freeze anything from a distance."; break;
        case 586 : texte = "You find the Master Sword!!!*Even Ganon could not stand up to its power!!! (in theory)"; break;
        case 587 : texte = "Congratulation Link, you have succeeded in saving me!!!***Let's find Ganon quickly, we have to reclaim the Triforce!"; break;
        case 589 : texte = "The secret passage behind the throne room leads to Ganon. Hurry up!"; break;
        case 590 : texte = "We are very near, follow me!"; break;
        case 591 : texte = "I'm afraid you are not able to defeat Ganon with your present weapons...*Go and speak to the chief of the village Kakariko, I am sure he will find a solution."; break;
        case 592 : texte = "Ganon is just behind that door, I will cure your wounds."; break;
        case 593 : texte = "Ganon is still somewhere in the castle."; break;
        case 594 : texte = "You should wait princess Zelda!!!"; break;
        case 595 : texte = "Wouldn't you have the spooky feeling to forget someone by any chance???"; break;
        case 596 : texte = "Zelda is waiting for you!!!"; break;
        case 597 : texte = "You find the Triforce!!!"; break;
        case 598 : texte = "You find the book of Mudora!!!**From now on, you understand the ancient Hylian!!!"; break;
        case 599 : texte = "Congratulation Link, for finding me. As a reward, I give you the Din Pendent, it raises your defense by one point."; break;
        case 600 : texte = "Congratulation Link, for finding me. As a reward, I give you the Nayru Pendent, it rises your defense by two points!!!"; break;
        case 601 : texte = "..."; break;
        case 602 : texte = "You obtain a magic pendent!!!**Your defense just raised!!!"; break;
        case 603 : texte = "Congratulation Link, for finding me. As a reward, I will double the busload of your magic meter!!!"; break;
        case 604 : texte = "Your magic meter is twofold!!!"; break;
        case 605 : texte = "Come back when you have an empty bottle and I will sell you a red potion which restores energy."; break;
        case 606 : texte = "A red potion for 60 rupees, are you interested?*              YES ?            no  "; break;
        case 607 : texte = "A red potion for 60 rupees, are you interested?*              yes              NO ?"; break;
        case 608 : texte = "Thank you, here is your potion.";break;
        case 609 : texte = "You get a red potion!!!*Drink it to restore your energy!!!"; break;
        case 610 : texte = "You get a green potion!!!*Drink it to restore your magic!!!"; break;
        case 611 : texte = "You get a blue potion!!!*Drink it to restore your energy and your magic!!!"; break;
        case 612 : texte = "Hello, what would you like to drink?"; break;
        case 613 : texte = "-Hiccup!- A fairy is said to give enchanted objects... -Hiccup!- ...to the adventurers who would find her... -Hiccup!!!-"; break;
        case 614 : texte = "One heart for 10 rupees, ok?**              YES ?            no  "; break;
        case 615 : texte = "One heart for 10 rupees, ok?**              yes              NO ?"; break;
        case 616 : texte = "A little bit of magic for 20 rupees, ok?**              YES ?            no  "; break;
        case 617 : texte = "A little bit of magic for 20 rupees, ok?**              yes              NO ?"; break;
        case 618 : texte = "Some magic for 30 rupees, ok?**              YES ?            no  "; break;
        case 619 : texte = "Some magic for 30 rupees, ok?**              yes              NO ?"; break;
        case 620 : texte = "5 arrows for 30 rupees, ok?**              YES ?            no  "; break;
        case 621 : texte = "5 arrows for 30 rupees, ok?**              yes              NO ?"; break;
        case 622 : texte = "One bomb for 30 rupees, ok?**              YES ?            no  "; break;
        case 623 : texte = "One bomb for 30 rupees, ok?**              yes              NO ?"; break;
        case 624 : texte = "One bow for 1000 rupees, ok?**              YES ?            no  "; break;
        case 625 : texte = "One bow for 1000 rupees, ok?**              yes              NO ?"; break;
        case 626 : texte = "One bow for 50 rupees, ok?**              YES ?            no  "; break;
        case 627 : texte = "One bow for 50 rupees, ok?**              yes              NO ?"; break;
        case 628 : texte = "You don't need this right now."; break;
        case 629 : texte = "Thank you."; break;
        case 630 : texte = "You get the bow!!!*Use it to reach a distant target."; break;
        case 631 : texte = "Choose what you want."; break;
        case 632 : texte = "What???*You are in mission for the chief???*Okay, so I'm going to give you a discount for the bow"; break;
        case 633 : texte = "Hello Link, I am the chief of that village, I suspected you were coming."; break;
        case 634 : texte = "Since this morning, monsters stride along Hyrule, I tried to talk about that with Zelda, but as you perhaps already saw, a powerful spell blocks the access to the castle..."; break;
        case 636 : texte = "You say Ganon is responsible for all of that? He stole the Triforce and he holds the princess Zelda captive?"; break;
        case 637 : texte = "Mmmm... The situation is more serious than I thought..."; break;
        case 638 : texte = "We have to act very quickly, you must face Ganon again!"; break;
        case 639 : texte = "How to go in the castle? I may have an idea..."; break;
        case 640 : texte = "As you know, the power of the 7 wise men was locked in 7 crystals by wizard Aghanim when he was trying to open up the path to the Dark World, where Ganon was."; break;
        case 641 : texte = "Yet, even if you raised the descendants of the 7 wise men from death after you defeated Ganon and found the Triforce, these crystals have kept their power."; break;
        case 642 : texte = "They have been hidden deep in the 7 temples, gather them all, and you'll be able to get over Ganon's spell."; break;
        case 643 : texte = "However that won't be easy, Ganon will surely send his best units to protect these crystals..."; break;
        case 644 : texte = "A last thing, you won't go far with your present equipment. Go and see the arms dealer and tell him that you're coming on my behalf. He will probably make a gesture for you."; break;
        case 645 : texte = "Go and see the arms dealer and tell him that you're coming on my behalf. He will probably make a gesture for you."; break;
        case 646 : texte = "You have to gather the 7 crystals to have a chance to save Zelda and Hyrule..."; break;
        case 647 : texte = "You found the 7 crystals? So go right now to the castle, first you have to deliver the princess, she will know better than I how to save Hyrule."; break;
        case 648 : texte = "Your weapons are null and void against Ganon? Therefore, you have to find the Master Sword. It is said to have been concealed in a hidden temple.*Besides, the way leading to the Sword of Evils Bane is said to cross over a village populated by monsters...*I wonder if such a village exists..."; break;
        case 650 : texte = "However, I'm afraid that your present equipment is inadequate to reach this temple, you may go to see the blacksmith of Gerudo village..."; break;
        case 651 : texte = "It's about time to brave Ganon and take the Triforce back!"; break;
        case 652 : texte = "Hey! You have to pay to open one of my chests!!!"; break;
        case 653 : texte = "One of these chests contains a piece of heart, do you want to try for 10 rupees?*You will be allowed to open just one chest, ok?               YES ?            no  "; break;
        case 654 : texte = "One of these chests contains a piece of heart, do you want to try for 10 rupees?*You will be allowed to open just one chest, ok?               yes              NO ?"; break;
        case 655 : texte = "Choose a chest."; break;
        case 656 : texte = "I don't have anymore prizes to bring into play, sorry."; break;
        case 657 : texte = "You lose! This chest is empty. Try again!"; break;
        case 658 : texte = "Hello! If you are looking for the blacksmith, he lives a little farther."; break;
        case 659 : texte = "Hello Link, I am the chief of this village.*You should go to see the blacksmith and show him what you want him to temper in your equipment."; break;
        case 660 : texte = "I have been informed of your quest, so I have arranged it with him.*All will be free for you."; break;
        case 661 : texte = "You don't need to drink this potion now."; break;
        case 662 : texte = "A green potion for 40 rupees, are you interested?*              YES ?            no  "; break;
        case 663 : texte = "A green potion for 40 rupees, are you interested?*              yes              NO ?"; break;
        case 664 : texte = "Come back when you have an empty bottle and I will sell you a green potion which restores magic."; break;
        case 665 : texte = "Come back later, I am overbooked!"; break;
        case 666 : texte = "May I do something for you?"; break;
        case 667 : texte = "Do you want me to temper your sword?**              YES ?            no  "; break;
        case 668 : texte = "Do you want me to temper your sword?**              yes              NO ?"; break;
        case 669 : texte = "Your sword triples in power and you can now throw some magic attack, so good!!!*"; break;
        case 670 : texte = "Do you want me to upgrade your gloves?**              YES ?            no  "; break;
        case 671 : texte = "Do you want me to upgrade your gloves?**              yes              NO ?"; break;
        case 672 : texte = "The power of your gloves helps you to lift heavy rocks."; break;
        case 673 : texte = "Do you want me to upgrade your bow?**              YES ?            no  "; break;
        case 674 : texte = "Do you want me to upgrade your bow?**              yes              NO ?"; break;
        case 675 : texte = "Your bow now shoots silver arrows with a cataclysmic power!!!"; break;
        case 676 : texte = "Come back when you have an empty bottle and I will sell you a blue potion which restores energy and magic."; break;
        case 677 : texte = "A blue potion for 160 rupees, are you interested?*              YES ?            no  "; break;
        case 678 : texte = "A blue potion for 160 rupees, are you interested?*              yes              NO ?"; break;
        case 679 : texte = "Our village has been constituted in the aim to stop careless adventurers from reaching the temple, I don't allow just anyone to pass."; break;
        case 680 : texte = "Mmmm... You already found 4 crystals?*I have got to admit you impress me..."; break;
        case 681 : texte = "All right, you are allowed to cross over the graveyard, at your own risk."; break;
        case 682 : texte = "Talk to the guard at the north of the village, he will let you pass."; break;
        case 683 : texte = "I see you're still alive...*Surprising."; break;
        case 684 : texte = "The dark temple is the starting point of the way reaching a legendary object. This village just exists to dissuade adventurers from approaching."; break;
        case 685 : texte = "So you found the Sword?*But don't believe it is yours for all that."; break;
        case 686 : texte = "The Master Sword is among the most treasured heritage of Hyrule with the Triforce, you will have to bring it back in his sanctuary when your mission is completed."; break;
        case 687 : texte = "All the inhabitants of this village are spirits who responded to princess Zelda's call."; break;
        case 688 : texte = "When you returned peace to Hyrule and reunified the Light World with the Golden Land, Zelda secretly asked volunteer spirits to create this village to block"; break;
        case 689 : texte = "the access to a very high valued object."; break;
        case 690 : texte = "Welcome Link!*Let me explain to you what I am doing here."; break;
        case 691 : texte = "As you certainly have noticed, monsters appeared in Hyrule. It's the first time I can see monsters since your victory on Ganon."; break;
        case 692 : texte = "Well, I have decided to list all of them."; break;
        case 693 : texte = "Unfortunately, I'm really too fearful to meet them, so I need your help."; break;
        case 694 : texte = "You have to fight each kind of monster and come to give me your report."; break;
        case 695 : texte = "Each time you have defeated 7 new kinds of enemies, I will give you one piece of heart."; break;
#ifdef __vita__
        case 696 : texte = "If you want to see what enemies you've already defeated, press ¾6"; break;
#else
        case 696 : texte = "If you want to see what enemies you've already defeated, press M."; break;
#endif
        case 697 : texte = "Again "+s+" different enemies before the next reward."; break;
        case 698 : texte = "You just lack only one enemy before the next reward!!!"; break;
        case 699 : texte = "Take this gift for your contribution on my project:"; break;
        case 700 : texte = "I'm sorry, but I don't have a gift for you anymore..."; break;
        case 701 : texte = "I can't take it in, you succeeded in defeating all kinds of enemies!!!*Congratulation Link!!!"; break;
        case 702 : texte = "                    Level 1:**                  Forest Temple"; break;
        case 703 : texte = "                    Level 2:**                  Water Temple"; break;
        case 704 : texte = "                    Level 3:**                 Mountain Temple"; break;
        case 705 : texte = "                    Level 4:**                  Desert Temple"; break;
        case 706 : texte = "                    Level 5:**                   Dark Temple"; break;
        case 707 : texte = "                    Level 6:**                   Fire Temple"; break;
        case 708 : texte = "                    Level 7:**                   Ice Temple"; break;
        case 709 : texte = "                    Level ?:**                  Hidden Temple"; break;
        case 710 : texte = "                  Last Level:**                 Hyrule Castle"; break;
        case 711 :texte = "                 Already tired?                  ?                 CONTINUE                 ?                   Save and quit                               Quit without saving            "; break;
        case 712 :texte = "                 Already tired?                                    Continue                     ?               SAVE AND QUIT              ?                Quit without saving            "; break;
        case 713 :texte = "                 Already tired?                                    Continue                                     Save and quit                  ?            QUIT WITHOUT SAVING           ?"; break;
        case 714 : texte = "At the right time when Link touched the Triforce, monsters disappeared and peace recurred.**Then Princess Zelda made a great decision: she touched in turn the Triforce and made her wish.**Triforce had always been the origin of troubles in the Kingdom, sooner or later, another evil creature would find it.**Just when princess touched the relic, it disappeared from Hyrule forever."; break;
        case 715 : texte = "Since this day, Hyrule people have lived in peace, without fear of new disasters.**Thus the legend of Zelda, of the Triforce and of the Golden Land is achieved.**Master Sword is said to rest safely somewhere and to be the last heirloom of Link's quest..."; break;
        case 716 : texte = "Congratulation Link, for finding me. As a reward, I give you the Farore Pendent, it raises your defense by one point..."; break;
        case 717 : texte = "Do you want to save your game?**                    ? YES ?*                      no  "; break;
        case 718 : texte = "Do you want to save your game?**                      yes  *                    ? NO ?"; break;
        case 719 : texte = "Game saved."; break;
        case 720 : texte = "The Kingdom of Hyrule has been in peace since Link, the last knight of Hyrule, had defeated the malicious Ganon and reclaimed the precious Triforce to him."; break;
        case 721 : texte = "Nobody knows what Link's wish to the Triforce was, but it had the effect of reunifying the Light and Dark World, and upraising the 7 wise men's descendants."; break;
        case 722 : texte = "Next, Link handed Triforce and Master Sword over to Princess Zelda, and people started to believe that peace would last.*But the people were wrong..."; break;
        case 723 : texte = "Unfortunately, Link's wish also had negative effects. Ganon and his henchmen were resurrected and got ready to attack."; break;
        case 724 : texte = "Somewhere in Hyrule Forest, Link is sleeping without suspecting that Ganon has already moved into the attack, until a"; 
        case 725 : texte = "well-known voice talk to him during his sleep..."; break;
        case 726 : texte = "Help me!*Help me!*That's me! Zelda!*I'm talking to you by telepathy."; break;
        case 727 : texte = "I am a prisoner in the dungeon of the castle!*I need your help!*Ganon is back, and he surely has already found the Triforce..."; break;
        case 728 : texte = "Come quickly to the castle Link, you are my only hope..."; break;
        case 729 : texte = "HELP: Press Select to consult help."; break;
        default : 
            texte = "TEXT ERROR";
    }

    return texte;
}

std::string Texte::getTexteFR(int id, std::string s){
    std::string texte = "";
    switch(id) {
        // 0 -> 99 : Carte
        case 0 : 
            texte = "Temple de la forêt"; 
            break;
        case 1 : 
            texte = "Temple de l'eau"; 
            break;
        case 2 : 
            texte = "Temple de la montagne";
            break;
        case 3 : 
            texte = "Temple du désert"; 
            break;
        case 4 : 
            texte = "Temple de l'ombre"; 
            break;
        case 5 : 
            texte = "Temple du feu"; 
            break;
        case 6 : 
            texte = "Temple de la glace"; 
            break;
        case 7 : 
            texte = "Temple secret"; 
            break;
        case 8 : 
            texte = "Château d'Hyrule"; 
            break;

        // 100 -> 199 : Encyclopedie
        case 100 : 
            texte = "MONSTRES " + s;
            break;
            
        // 200 -> 299 : Generique
        case 200 :
            texte = "ECRAN DE SELECTION";
            break;
        case 201 : 
            texte = "1.";
            break;
        case 202 :
            texte = "2.";
            break;
        case 203 : 
            texte = "3.";
            break;
        case 204 :
            texte = "OPTIONS";
            break;
        case 205 :
            texte = "RECORDS";
            break;
        case 206 :
            texte = "OPTIONS";
            break;
        case 207 :
            texte = "MUSIQUE";
            break;
        case 208 :
            texte = "SON";
            break;
        case 209 :
            texte = "RETOUR";
            break;
        case 210 :
            texte = "RECORDS";
            break;
        case 211 :
            texte = "MEILLEUR TEMPS : " + s;
            break;
        case 212 :
            texte = "RANG DES 100%";
            break;
        case 213 :
            texte = "RANG ULTIME";
            break;
        case 214 :
            texte = "RANG DE RAPIDITE";
            break;
        case 215 :
            texte = "RETOUR";
            break;
        case 216 :
            texte = "EFFACER";
            break;
        case 217 :
            texte = "EFFACER ?";
            break;
        case 218 :
            texte = "OUI";
            break;
        case 219 :
            texte = "NON";
            break;
        case 220 :
            texte = "CHARGER";
            break;
        case 221 :
            texte = "EFFACER";
            break;
        case 222 :
            texte = "ANNULER";
            break;
        case 223 :
            texte = "AIDE 1/2";
            break;
        case 224 :
#ifdef __vita__
            texte = "Retour au jeu : ¾3 - Suite : ¾5";
#else
            texte = "Retour au jeu : Entrée - Suite : Droite";
#endif
            break;
        case 225 :
#ifdef __vita__
            texte = "Lire / Ouvrir / Parler : ¾2";
#else
            texte = "Lire / Ouvrir / Parler : Espace";
#endif
            break;
        case 226 :
#ifdef __vita__
            texte = "Valider / Passer texte : ¾3";
#else
            texte = "Valider / Passer texte : Entrée";
#endif
            break;
        case 227 :
#ifdef __vita__
            texte = "Déplacer Link : ¾9 Gauche";
#else
            texte = "Déplacer Link : Flèches de direction";
#endif
            break;
        case 228 :
#ifdef __vita__
            texte = "Courir : L (maintenu) / R";
#else
            texte = "Courir : Shift maintenu ou Caps lock";
#endif
            break;
        case 229 :
#ifdef __vita__
            texte = "Coup d'épée : ¾4";
#else
            texte = "Coup d'épée : W ou Z";
#endif
            break;
        case 230 :
#ifdef __vita__
            texte = "Attaque Tornade : ¾4 maintenu puis lâché";
#else
            texte = "Attaque Tornade : W ou Z maintenu puis lâché";
#endif
            break;
        case 231 :
#ifdef __vita__
            texte = "Menu de sélection d'objet : ¾5";
#else
            texte = "Menu de sélection d'objet : Entrée";
#endif
            break;
        case 232 :
#ifdef __vita__
            texte = "Utiliser l'objet sélectionné : ¾1";
#else
            texte = "Utiliser l'objet sélectionné : X";
#endif
            break;
        case 233 :
#ifdef __vita__
            texte = "Porter sans équiper les gants : ¾3";
#else
            texte = "Porter sans équiper les gants : C";
#endif
            break;
        case 234 :
#ifdef __vita__
            texte = "Afficher la carte : ¾7 (ext/donjons)";
#else
            texte = "Afficher la carte : P (dans les donjons)";
#endif
            break;
        case 235 :
#ifdef __vita__
            texte = "Afficher la carte : L (ext/donjons)";
#else
            texte = "Afficher la carte : P (dans les donjons)";
#endif
            break;
        case 236 :
#ifdef __vita__
            texte = "Afficher les monstres vaincus : ¾6";
#else
            texte = "Afficher les monstres vaincus : M";
#endif
            break;
        case 237 :
#ifdef __vita__
            texte = "Regarder autour : ¾9 Droite";
#else
            texte = "Regarder autour : Ctrl et direction";
#endif
            break;
        case 238 :
#ifdef __vita__
            texte = "Sauvegarder / Quitter : Start";
#else
            texte = "Sauvegarder / Quitter : Echap";
#endif
            break;
        case 239 :
#ifdef __vita__
            texte = "";
#else
            texte = "Agrandir / Rétrécir : Ctrl et Entrée";
#endif
            break;
        case 240 :
            texte = "AIDE 2/2";
            break;
        case 241 :    
#ifdef __vita__
            texte = "Retour au jeu : ¾3 - Précédent : ¾7";
#else
            texte = "Retour au jeu : Entrée - Précédent : Gauche";
#endif
            break;
        case 242 :
#ifdef __vita__
            texte = "Utilise objet sélectionné: ¾1";
#else
            texte = "Utilise objet sélectionné: X";
#endif
            break;
        case 243 :
#ifdef __vita__
            texte = "Porter sans équiper les gants : ¾3"; 
#else
            texte = "Porter sans équiper les gants : C"; 
#endif
            break;
        case 244 :
#ifdef __vita__
            texte = "Afficher la carte : ¾7 (ext/donjon)";
#else
            texte = "Afficher la carte : P (extérieur ou donjons)";
#endif
            break;
        case 245 :
#ifdef __vita__
            texte = "Afficher la carte : ¾7 (dans les donjons)";
#else
            texte = "Afficher la carte : P (dans les donjons)";
#endif
            break;
        case 246 :
#ifdef __vita__
            texte = "Afficher les monstres vaincus : ¾6";
#else
            texte = "Afficher les monstres vaincus : M";
#endif
            break;
        case 247 :
#ifdef __vita__
            texte = "Regarder autour : ¾9 Droite";
#else
            texte = "Regarder autour : Ctrl et direction";
#endif
            break;
        case 248 :
#ifdef __vita__
            texte = "Sauvegarder / Quitter : Start";
#else
            texte = "Sauvegarder / Quitter : Echap";
#endif
            break;
        case 249 :
#ifdef __vita__
            texte = "";
#else
            texte = "Agrandir / Rétrécir : Ctrl et Entrée";
#endif
            break;

        case 250 :
            texte = "RANG : Héros d'Hyrule";
            break;
        case 251 :
            texte = "RANG : INCONNU";
            break;
        case 252 :
            texte = "Finir le jeu à 100%";
            break;
        case 253 :
            texte = "RANG : Frimeur";
            break;
        case 254 :
            texte = "RANG : INCONNU";
            break;
        case 255 :
            texte = "Finir le jeu sans mourir,";
            break;
        case 256 :
            texte = "avec 10 coeurs au maximum,";
            break;
        case 257 :
            texte = "sans parler aux Grandes Fées,";
            break;
        case 258 :
            texte = "sans acheter de flacons";
            break;
        case 259 :
            texte = "et sans prendre le bouclier.";
            break;
        case 260 :
            texte = "RANG : Marathonien d'Hyrule";
            break;
        case 261 :
            texte = "RANG : INCONNU";
            break;
        case 262 :
            texte = "Finir le jeu en moins de";
            break;
        case 263 :
            texte = "deux heures";
            break;
        case 264 : 
            texte = "SCORES :";
            break;
        case 265 :
            texte = "Temps de jeu : " + s;
            break;
        case 266 :
            texte = "Mort " + s + " fois";
            break;
        case 267 :
            texte = "Mort " + s + " fois";
            break;
        case 268 :
            texte = "Quarts de coeurs : " + s + " / 36";
            break;
        case 269 :
            texte = "Objets : " + s + " / 56";
            break;
        case 270 :
            texte = "Types d'ennemis vaincus : " + s + " / 46";
            break;
        case 271 :
            texte = "Tu as fini ce jeu à " + s + "%, félicitation !";
            break;
        case 272 :
            texte = "RANG : ";
            break;
        case 273 :
            texte = " - Frimeur";
            break;
        case 274 :
            texte = " - Héros d'Hyrule";
            break;
        case 275 :
            texte = " - Perfectionniste";
            break;
        case 276 :
            texte = " - Fan de Zelda";
            break;
        case 277 :
#ifdef __vita__
            texte = " - Pro du pad";
#else
            texte = " - Pro du clavier";
#endif
            break;
        case 278 :
            texte = " - Confirmé";
            break;
        case 279 :
            texte = " - Débutant";
            break;
        case 280 :
            texte = " - Mort-vivant";
            break;
        case 281 : 
            texte = " - Kamikaze";
            break;
        case 282 :
            texte = " - Marathonien d'Hyrule";
            break;
        case 283 :
            texte = "LANGUE";
            break;
        case 284 :
            texte = "Française";
            break;

        // 300 -> 399 : Menu
        case 300 :
            texte = "X";
            break;
        case 301 :
            texte = "STATUT :";
            break;
        case 302 :
            texte = "VIE       : " + s;
            break;
        case 303 :
            texte = "MAGIE     : " + s;
            break;
        case 304 :
            texte = "FORCE     : " + s;
            break;
        case 305 :
            texte = "DEFENSE   : " + s;
            break;
        case 306 :
            texte = "TEMPS     : " + s;
            break;
        case 307 :
            texte = "CRISTAUX :";
            break;

        // 500 -> ?? : Texte
        case 501 : texte = "Tu as trouvé un bouclier !!!**Ta défense augmente d'un point !"; break;
#ifdef __vita__
        case 502 : texte = "Tu as trouvé une épée !!!**Tu vas pouvoir te défendre face aux monstres avec la touche ¾4 !!!*Maintiens ¾4 enfoncé pour charger une attaque cyclone !!!"; break;
#else
        case 502 : texte = "Tu as trouvé une épée !!!**Tu vas pouvoir te défendre face aux monstres avec la touche W (ou Z) !!!*Maintiens W enfoncé pour charger une attaque cyclone !!!"; break;
#endif
        case 503 : texte = "Tu as trouvé un quart de coeur !!!"; break;
        case 504 : texte = "Encore "+s+" et tu gagneras un coeur supplémentaire !!!"; break;
        case 505 : texte = "Ton nombre de coeurs vient d'augmenter !!!"; break;
        case 511 : texte = "N : Maison de Link*O : Plaine d'Hyrule*E : Temple de la Forêt"; break;
        case 512 : texte = "Temple de la Montagne**Déconseillé aux cardiaques, peureux, et aux âmes sensibles en général."; break;
        case 513 : texte = "O : Entrée du Désert*N : Temple de la Montagne"; break;
        case 514 : texte = "N : Temple de la Montagne*S : Plaine d'Hyrule"; break;
        case 515 : texte = "N : Mont du Péril"; break;
        case 516 : texte = "E : Entrée de la Forêt"; break;
        case 517 : texte = "S : Lac Hylia*E : Cimetière Hanté"; break;
        case 518 : texte = "S : Vers le Village Cocorico"; break;
        case 519 : texte = "N : Village Cocorico"; break;
        case 520 : texte = "N : Plaine d'Hyrule"; break;
        case 521 : texte = "O : Terres de Feu"; break;
        case 522 : texte = "E : Village de l'Ombre*- Déconseillé aux vivants -"; break;
        case 523 : texte = "Temple des Ténèbres**Si vous êtes un fantôme et que vous cherchez un job, venez plutôt chômer ici."; break;
        case 524 : texte = "N : Village de l'Ombre*O : Lac Hylia"; break;
        case 525 : texte = "N : Cimetière Hanté**Entrée interdite"; break;
        case 526 : texte = "Village de l'Ombre"; break;
        case 527 : texte = "Je vends un flacon pour 100 rubis, ça t'intéresse ?*              OUI ?            non  "; break;
        case 528 : texte = "Je vends un flacon pour 100 rubis, ça t'intéresse ?*              oui              NON ?"; break;
        case 529 : texte = "Désolé, mais tu n'as pas assez de rubis."; break;
        case 530 : texte = "Merci beaucoup, voilà ton flacon."; break;
        case 531 : texte = "Reviens me voir si tu changes d'avis."; break;
        case 532 : texte = "Désolé, c'était mon seul flacon."; break;
        case 533 : texte = "Tu as trouvé un flacon vide !!!**Tu vas pouvoir t'en servir pour stocker des potions !!!"; break;
        case 535 : texte = "Les habitants de ce village ont un dialecte très particulier, je n'y comprends rien..."; break;
        case 536 : texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 537 : texte = "Obtiens une autorisation du chef si tu veux vraiment passer!!!"; break;
        case 538 : texte = "Le chef t'as autorisé à passer ??? Grrrr... Alors écarte toi!!!"; break;
        case 539 : texte = "Ne traîne pas dans mes pattes !!!"; break;
        case 540 : texte = "On n'a pas l'habitude de voir des visiteurs par ici..."; break;
        case 541 : texte = "Les monstres du coin ne craignent pas grand chose, heureusement qu'ils n'attaquent que les humains."; break;
        case 542 : texte = "C'est vrai ?*Tu comprends ce que je dis ?"; break;
        case 543 : texte = "N : Désert et Village Gerudo"; break;
        case 544 : texte = "S : Lac Hylia*O : Château d'Hyrule"; break;
        case 545 : texte = "Village Cocorico"; break;
        case 546 : texte = "O : Château d'Hyrule"; break;
        case 547 : texte = "Quelle belle journée !!!"; break;
        case 548 : texte = "Pourquoi ai-je accepté de m'occuper de ces saletés ???*J'ai horreur des poules !!!"; break;
        case 549 : texte = "On trouve des tas de choses dans les boutiques du village."; break;
        case 550 : texte = "S : Village Cocorico*O : Désert*E : Mont du Péril"; break;
        case 551 : texte = "Village Gerudo"; break;
        case 552 : texte = "Perdu dans le désert ?*Vous êtes ici :*                        X"; break;
        case 554 : texte = "S : Vers le Château d'Hyrule"; break;
        case 555 : texte = "Temple du Désert**Venez essayer nos bains.*(eau non-potable)"; break;
        case 556 : texte = "Temple de la Forêt**Sauvez les arbres, mangez du castor!!!"; break;
        case 557 : texte = "Temple du Lac**Bonnet de bain obligatoire."; break;
        case 558 : texte = "Temple de Glace**Le personnel tient à rappeler qu'un donjon n'est pas une patinoire."; break;
        case 559 : texte = "As-tu été voir le forgeron de ce village ?*On dit qu'il est très doué pour améliorer l'équipement des aventuriers, beaucoup de monde lui rend visite."; break;
        case 560 : texte = "Le temple se trouve au fin fond du désert, à la place d'une ancienne oasis."; break;
        case 561 : texte = "S : Terres de Feu*E : Village Cocorico"; break;
        case 562 : texte = "Château d'Hyrule"; break;
        case 563 : texte = "E : Village Cocorico"; break;
        case 564 : texte = "O : Roc de la Tortue*E : Lac Hylia"; break;
        case 565 : texte = "Temple Caché**Ici repose la lame purificatrice, Excalibur."; break;
        case 566 : texte = "N : Vers le cimetière hanté"; break;
#ifdef __vita__
        case 567 : texte = "Tu as trouvé la carte du donjon !!!*Appuie sur ¾7 pour voir le plan."; break;
#else
        case 567 : texte = "Tu as trouvé la carte du donjon !!!*Appuie sur P pour voir le plan."; break;
#endif
        case 568 : texte = "Tu as trouvé la boussole !!!*Tu peux localiser le boss et les coffres sur le plan."; break;
        case 569 : texte = "Tu as trouvé la clé du boss !!!"; break;
        case 570 : texte = "Tu as trouvé une petite clé !!!*Approche une porte pour l'ouvrir."; break;
#ifdef __vita__
        case 571 : texte = "Tu as trouvé les gants !!!*Utilise-les pour soulever des objets en les équipant ou en appuyant sur ¾3."; break;
#else        
        case 571 : texte = "Tu as trouvé les gants !!!*Utilise-les pour soulever des objets en les équipant ou en appuyant sur C."; break;
#endif        
        case 572 : texte = "Tu as trouvé un cristal magique !!!"; break;
        case 573 : texte = "A quoi pourra-t-il bien servir ?"; break;
        case 574 : texte = "Il en reste encore "+s+" à trouver !!!"; break;
        case 575 : texte = "Plus que 2 à trouver !!!"; break;
        case 576 : texte = "Il ne t'en manque plus qu'un seul !!!"; break;
        case 577 : texte = "Tu as tous les cristaux, cours au château sauver Zelda !!!"; break;
        case 580 : texte = "Tu as trouvé le grappin !!!*Utilise-le pour franchir des obstacles."; break;
        case 581 : texte = "Tu as trouvé la lanterne !!!*Utilise-la pour faire jaillir des flammes."; break;
        case 582 : texte = "Tu as trouvé les palmes !!!*Equipe-les pour aller dans l'eau."; break;
        case 583 : texte = "Tu as trouvé le marteau magique !!!*Utilise-le pour écraser les obstacles."; break;
        case 584 : texte = "Tu as trouvé le baton de feu !!!*Tu peux désormais lancer de puissantes flammes à distance."; break;
        case 585 : texte = "Tu as trouvé le baton de glace !!!*Utilise-le pour tout congeler à distance."; break;
        case 586 : texte = "Tu as trouvé Excalibur !!!*Même Ganon ne devrait pas pouvoir résister à sa puissance !!! (en théorie)"; break;
        case 587 : texte = "Félicitation Link, tu as réussi à venir me délivrer!!!***Allons vite trouver Ganon, il faut impérativement lui reprendre la Triforce !"; break;
        case 589 : texte = "Le passage secret derrière la salle du trône mène à Ganon. Dépêchons-nous !"; break;
        case 590 : texte = "Nous y sommes presque, suis-moi !"; break;
        case 591 : texte = "J'ai bien peur que tu ne puisses jamais vaincre Ganon avec tes armes actuelles...*Va parler au chef du village Cocorico, je suis sûre qu'il trouvera une solution."; break;
        case 592 : texte = "Ganon est juste derrière cette porte, je vais soigner tes blessures."; break;
        case 593 : texte = "Ganon est toujours quelque part dans le château."; break;
        case 594 : texte = "Tu devrais attendre la princesse Zelda !!!"; break;
        case 595 : texte = "Tu n'aurais pas l'étrange sentiment d'oublier quelqu'un par hasard ???"; break;
        case 596 : texte = "Zelda t'attend!!!"; break;
        case 597 : texte = "Tu as trouvé la Triforce!!!"; break;
        case 598 : texte = "Tu as trouvé le livre de Mudora!!!**Tu comprends désormais le Hylien ancien!!!"; break;
        case 599 : texte = "Félicitation Link, tu as réussi à me trouver. En récompense, je t'offre le médaillon de Din, il augmente ta défense d'un point."; break;
        case 600 : texte = "Félicitation Link, tu as réussi à me trouver. En récompense, je t'offre le médaillon de Nayru, il augmente ta défense de deux points!!!"; break;
        case 601 : texte = "..."; break;
        case 602 : texte = "Tu as obtenu un médaillon magique !!!**Ta défense vient d'augmenter!!!"; break;
        case 603 : texte = "Félicitation Link, tu as réussi à me trouver. Pour te récompenser, je vais doubler la capacité de ta réserve de magie!!!"; break;
        case 604 : texte = "Ta réserve de magie a doublé!!!"; break;
        case 605 : texte = "Reviens me voir quand tu auras un flacon vide  et je te vendrai une potion rouge qui restaure l'énergie."; break;
        case 606 : texte = "Une potion rouge pour 60 rubis, ça t'intéresse?*              OUI ?            non  "; break;
        case 607 : texte = "Une potion rouge pour 60 rubis, ça t'intéresse?*              oui              NON ?"; break;
        case 608 : texte = "Merci, voilà ta potion.";break;
        case 609 : texte = "Tu as obtenu une potion rouge !!!*Bois-la pour restaurer ton énergie!!!"; break;
        case 610 : texte = "Tu as obtenu une potion verte !!!*Bois-la pour restaurer ta magie!!!"; break;
        case 611 : texte = "Tu as obtenu une potion bleue !!!*Bois-la pour restaurer ton énergie et ta magie!!!"; break;
        case 612 : texte = "Bonjour, je vous sers quelque chose ?"; break;
        case 613 : texte = "Hic! On raconte qu'une fée donnerait des objets enchantés... Hic! ...aux aventuriers qui la  trouveraient... Hic!!!"; break;
        case 614 : texte = "Un coeur pour 10 rubis, ok ?**              OUI ?            non  "; break;
        case 615 : texte = "Un coeur pour 10 rubis, ok ?**              oui              NON ?"; break;
        case 616 : texte = "Un peu de magie pour 20 rubis, ok ?**              OUI ?            non  "; break;
        case 617 : texte = "Un peu de magie pour 20 rubis, ok ?**              oui              NON ?"; break;
        case 618 : texte = "Beaucoup de magie pour 30 rubis, ok ?**              OUI ?            non  "; break;
        case 619 : texte = "Beaucoup de magie pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 620 : texte = "5 flèches pour 30 rubis, ok ?**              OUI ?            non  "; break;
        case 621 : texte = "5 flèches pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 622 : texte = "Une bombe pour 30 rubis, ok ?**              OUI ?            non  "; break;
        case 623 : texte = "Une bombe pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 624 : texte = "Un arc pour 1000 rubis, ok ?**              OUI ?            non  "; break;
        case 625 : texte = "Un arc pour 1000 rubis, ok ?**              oui              NON ?"; break;
        case 626 : texte = "Un arc pour 50 rubis, ok ?**              OUI ?            non  "; break;
        case 627 : texte = "Un arc pour 50 rubis, ok ?**              oui              NON ?"; break;
        case 628 : texte = "Tu n'as pas besoin de ça maintenant."; break;
        case 629 : texte = "Merci."; break;
        case 630 : texte = "Tu as obtenu l'arc !!!*Utilise-le pour atteindre des cibles éloignées."; break;
        case 631 : texte = "Choisis ce que tu veux."; break;
        case 632 : texte = "Hein ???*Tu es en mission pour le chef ???*Bon alors je vais te faire une réduction sur l'arc..."; break;
        case 633 : texte = "Bonjour Link, je suis le chef de ce village, je me doutais que tu passerais."; break;
        case 634 : texte = "Depuis ce matin des monstres sont apparus un peu partout à Hyrule, j'ai voulu aller en parler à la princesse Zelda, mais comme tu l'as peut-être déjà vu, un puissant sortilège bloque l'accès au château..."; break;
        case 636 : texte = "Tu dis que Ganon est responsable de tout ça ? Qu'il a volé la Triforce et qu'il détient la princesse Zelda prisonnière ?"; break;
        case 637 : texte = "Mmmm... la situation est plus grave que je le croyais..."; break;
        case 638 : texte = "Il faut agir au plus vite, tu dois affronter Ganon à nouveau!"; break;
        case 639 : texte = "Comment entrer dans le château ? J'ai peut-être une idée..."; break;
        case 640 : texte = "Comme tu le sais, le pouvoir des 7 sages a été enfermé dans 7 cristaux par le sorcier Aghanim alors qu'il tentait de lever le sceau qui confinait Ganon au monde des ténèbres."; break;
        case 641 : texte = "Or, bien que tu aies ressuscité les descendants des sages après avoir vaincu Ganon et trouvé la Triforce, ces cristaux ont conservé leur puissance."; break;
        case 642 : texte = "Ils ont été cachés au fin fond des 7 temples, réunis-les tous et tu pourras passer outre le sortilège de Ganon."; break;
        case 643 : texte = "Ce ne sera toutefois pas chose aisé, Ganon a certainement dû envoyer ses meilleurs éléments protéger ces cristaux..."; break;
        case 644 : texte = "Une dernière chose, tu n'iras pas loin avec ton équipement actuel. Va voir le marchand d'armes et dis-lui que tu viens de ma part. Il fera sûrement un geste pour toi."; break;
        case 645 : texte = "Va voir le marchand d'armes et dis-lui que tu viens de ma part, il fera certainement un geste pour toi."; break;
        case 646 : texte = "Il te faut rassembler les 7 cristaux pour avoir une chance de sauver Zelda et Hyrule..."; break;
        case 647 : texte = "Tu as trouvé les 7 cristaux ? Alors rends-toi au château, tu dois avant tout délivrer la princesse, elle saura mieux que moi comment sauver Hyrule."; break;
        case 648 : texte = "Tes armes sont sans effet sur Ganon ? Dans ce cas tu dois trouver Excalibur. On raconte qu'elle a été dissimulée dans un temple caché.*On dit aussi que le chemin menant à la lame purificatrice passe par un village peuplé de monstres...*Je me demande si un tel village existe..."; break;
        case 650 : texte = "Toutefois j'ai bien peur que ton équipement actuel soit insuffisant pour accéder à ce temple, tu devrais peut-être passer voir le forgeron du village Gerudo..."; break;
        case 651 : texte = "Il est temps d'affronter Ganon et de lui reprendre la Triforce!"; break;
        case 652 : texte = "Hey! Il faut payer pour ouvrir un de mes coffres!!!"; break;
        case 653 : texte = "Un de ces coffres contient un quart de coeur, tu veux tenter ta chance pour 10 rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?*              OUI ?            non  "; break;
        case 654 : texte = "Un de ces coffres contient un quart de coeur, tu veux tenter ta chance pour 10 rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?*              oui              NON ?"; break;
        case 655 : texte = "Choisis un coffre."; break;
        case 656 : texte = "Je n'ai plus de prix à mettre en jeu, désolé."; break;
        case 657 : texte = "Perdu! Ce coffre est vide."; break;
        case 658 : texte = "Bonjour! Si vous êtes venu voir le forgeron, il habite un peu plus loin."; break;
        case 659 : texte = "Bonjour Link, je suis le chef de ce village.*Tu devrais aller voir le forgeron et lui présenter ce que tu veux qu'il reforge dans ton équipement."; break;
        case 660 : texte = "J'ai été informé de ta quête, alors je me suis arrangé avec lui.*Tout sera gratuit pour toi."; break;
        case 661 : texte = "Tu n'as pas besoin de boire cette potion maintenant."; break;
        case 662 : texte = "Une potion verte pour 40 rubis, ça t'intéresse?*              OUI ?            non  "; break;
        case 663 : texte = "Une potion verte pour 40 rubis, ça t'intéresse?*              oui              NON ?"; break;
        case 664 : texte = "Reviens me voir quand tu auras un flacon vide et je te vendrai une potion verte qui restaure la magie."; break;
        case 665 : texte = "Reviens plus tard, je suis débordé!"; break;
        case 666 : texte = "Puis-je faire quelque chose pour toi ?"; break;
        case 667 : texte = "Veux-tu que je reforge ton épée ?**              OUI ?            non  "; break;
        case 668 : texte = "Veux-tu que je reforge ton épée ?**              oui              NON ?"; break;
        case 669 : texte = "Ton épée a triplé de puissance et peut désormais renvoyer certaines attaques magiques, trop bien !!!*"; break;
        case 670 : texte = "Veux-tu que j'améliore tes gants ?**              OUI ?            non  "; break;
        case 671 : texte = "Veux-tu que j'améliore tes gants ?**              oui              NON ?"; break;
        case 672 : texte = "La puissance de tes gants va te permettre de soulever de lourds rochers."; break;
        case 673 : texte = "Veux-tu que j'améliore ton arc ?**              OUI ?            non  "; break;
        case 674 : texte = "Veux-tu que j'améliore ton arc ?**              oui              NON ?"; break;
        case 675 : texte = "Ton arc tire désormais des flèches d'argent d'une puissance dévastatrice!!!"; break;
        case 676 : texte = "Reviens me voir quand tu auras un flacon vide et je te vendrai une potion bleue qui restaure l'énergie et la magie."; break;
        case 677 : texte = "Une potion bleue pour 160 rubis, ça t'intéresse?*              OUI ?            non  "; break;
        case 678 : texte = "Une potion bleue pour 160 rubis, ça t'intéresse?*              oui              NON ?"; break;
        case 679 : texte = "Notre village a été fondé pour empêcher les aventuriers imprudents d'accéder au temple, je ne donne pas l'autorisation de passer à n'importe qui."; break;
        case 680 : texte = "Mmmm... Tu as déjà trouvé 4 cristaux ?*Je dois avouer que tu m'impressionnes..."; break;
        case 681 : texte = "Bon c'est entendu, tu as l'autorisation de passer par le cimetière, à tes risques et périls."; break;
        case 682 : texte = "Va parler au garde au nord du village, il te laissera passer."; break;
        case 683 : texte = "Je vois que tu es toujours vivant...*Etonnant."; break;
        case 684 : texte = "Le temple de l'ombre constitue le point de départ du chemin menant à un objet de légende. Ce village ne sert qu'à dissuader les aventuriers de trop s'en approcher."; break;
        case 685 : texte = "Ainsi tu as trouvé l'Epée ?*Mais ne crois pas qu'elle soit à toi pour autant."; break;
        case 686 : texte = "Excalibur fait partie du patrimoine le plus précieux d'Hyrule avec la Triforce, tu devras la ramener dans son sanctuaire une fois ta mission achevée."; break;
        case 687 : texte = "Les habitants de ce village sont tous des esprits ayant répondu à l'appel de la princesse Zelda."; break;
        case 688 : texte = "Lorsque tu as ramené la paix sur Hyrule et réunifié le monde de la lumière avec la Terre d'Or, Zelda a secrètement demandé aux esprits volontaires de créer ce village pour bloquer"; break;
        case 689 : texte = "l'accès à un objet de très grande valeur."; break;        
        case 690 : texte = "Bienvenue Link!*Laisse-moi t'expliquer ce que je fais ici."; break;
        case 691 : texte = "Comme tu l'as certainement remarqué, des monstres sont apparus partout dans Hyrule. C'est la première fois que je vois des monstres depuis que tu as vaincu Ganon."; break;
        case 692 : texte = "Et bien j'ai décidé de tous les répertorier."; break;
        case 693 : texte = "L'ennui c'est que je suis bien trop peureux pour aller à leur rencontre, alors j'ai besoin de ton aide."; break;
        case 694 : texte = "Il faut que tu battes chaque type de monstre et que tu viennes me faire ton rapport."; break;
        case 695 : texte = "Je te récompenserai tous les 7 nouveaux types d'ennemis vaincus."; break;
#ifdef __vita__
        case 696 : texte = "Si tu veux savoir quels ennemis tu as déjà vaincu, appuye sur ¾6"; break;
#else
        case 696 : texte = "Si tu veux savoir quels ennemis tu as déjà vaincu, appuye sur M."; break;
#endif
        case 697 : texte = "Encore "+s+" ennemis différents avant la prochaine récompense."; break;
        case 698 : texte = "Plus qu'un nouvel ennemi avant la prochaine récompense!!!"; break;
        case 699 : texte = "Accepte ce cadeau pour ta contribution à mon projet :"; break;
        case 700 : texte = "Je suis désolé mais je n'ai plus rien à t'offrir..."; break;
        case 701 : texte = "Je n'en crois pas mes yeux, tu as réussi à vaincre chaque type d'ennemis !!!*Félicitation Link!!!"; break;        
        case 702 : texte = "                   Niveau 1 :**               Temple de la forêt"; break;
        case 703 : texte = "                   Niveau 2 :**                 Temple de l'eau"; break;
        case 704 : texte = "                   Niveau 3 :**              Temple de la montagne"; break;
        case 705 : texte = "                   Niveau 4 :**                Temple du désert"; break;
        case 706 : texte = "                   Niveau 5 :**                Temple de l'ombre"; break;
        case 707 : texte = "                   Niveau 6 :**                  Temple du feu"; break;
        case 708 : texte = "                   Niveau 7 :**                Temple de la glace"; break;
        case 709 : texte = "                   Niveau ? :**                   Temple secret"; break;
        case 710 : texte = "                 Niveau Final :**                Château d'Hyrule"; break;        
        case 711 :texte = "                Déjà fatigué ?                  ?                CONTINUER                  ?             Sauvegarder et quitter                        Quitter sans sauvegarder           "; break;
        case 712 :texte = "                Déjà fatigué ?                                   Continuer                     ?          SAUVEGARDER ET QUITTER           ?            Quitter sans sauvegarder           "; break;
        case 713 :texte = "                Déjà fatigué ?                                   Continuer                                Sauvegarder et quitter              ?         QUITTER SANS SAUVEGARDER          ?"; break;
        case 714 : texte = "A l'instant où Link toucha la Triforce, les monstres disparurent et la paix revint.**La princesse Zelda prit alors une grande décision: elle toucha à son tour la Triforce pour exaucer son voeu...**La Triforce fut depuis toujours à l'origine des problèmes survenus au Royaume, tôt ou tard un autre être malfaisant aurait fini par la trouver.**A la seconde où la princesse toucha la relique, elle disparue à jamais d'Hyrule.";
        case 715 : texte = "Depuis ce jour, le peuple d'Hyrule vécut en paix, sans craindre de nouveaux désastres.**Ainsi s'achève la légende de Zelda, celle de la  Triforce et de la Terre d'Or.**On dit que l'épée Excalibur repose en sûreté quelque part, et qu'elle constitue le dernier souvenir de la quête de Link..."; break;
        case 716 : texte = "Félicitation Link, tu as réussi à me trouver. En récompense, je t'offre le médaillon de Farore, il augmente ta défense d'un point."; break;
        case 717 : texte = "Souhaites-tu sauvegarder ta partie ?**                    ? OUI ?*                      non  "; break;
        case 718 : texte = "Souhaites-tu sauvegarder ta partie ?**                      oui  *                    ? NON ?"; break;
        case 719 : texte = "Partie sauvegardée."; break;
        case 720 : texte = "Le Royaume d'Hyrule était en paix depuis que Link, dernier chevalier hylien, avait vaincu le maléfique Ganon et lui avait repris la précieuse Triforce."; break;
        case 721 : texte = "Nul ne sait quel voeu fit Link en touchant la Triforce, mais il eut comme effet de réunifier le monde de la lumière et celui des ténèbres, et ramena à la vie les descendants des 7 sages."; break;
        case 722 : texte = "Link remit ensuite à la princesse Zelda la Triforce et l'épée Excalibur, et le peuple se mit à croire que la paix durerait.*Mais le peuple se trompait..."; break;
        case 723 : texte = "Le souhait de Link à la Triforce eu hélas de fâcheux effets. Ganon et ses sbires furent ainsi ressuscités et s'apprêtèrent à attaquer."; break;
        case 724 : texte = "Quelque part dans la forêt d'Hyrule, Link dort sans se douter que Ganon est passé à l'attaque, jusqu'à ce qu'"; break;
        case 725 : texte ="une voix familière lui parle dans son sommeil..."; break;
        case 726 : texte = "A l'aide!*A l'aide!*C'est moi! C'est Zelda!*Je te parle par télépathie."; break;
        case 727 : texte = "Je suis retenue prisonnière dans le donjon du château! J'ai besoin de ton aide!*Ganon est de retour, et il a certainement dû trouver la Triforce à l'heure qu'il est..."; break;
        case 728 : texte = "Viens vite au château Link, tu es mon seul espoir..."; break;
#ifdef __vita__
        case 729 : texte = "AIDE : Appuie sur Select pour consulter l'aide."; break;
#else
        case 729 : texte = "AIDE : Appuie sur F1 pour consulter l'aide."; break;
#endif
        default : 
            texte = "[ERREUR TEXTE]";
    }

    return texte;
}

std::string Texte::getTexteDE(int id, std::string s){
    std::string texte = "";
    switch(id) {
        // 0 -> 99 : Carte
        case 0 : 
            texte = "Wald-Tempel"; 
            break;
        case 1 : 
            texte = "Wasser-Tempel"; 
            break;
        case 2 : 
            texte = "Berg-Tempel";
            break;
        case 3 : 
            texte = "Wüsten-Tempel"; 
            break;
        case 4 : 
            texte = "Dunkler Tempel"; 
            break;
        case 5 : 
            texte = "Feuer-Tempel"; 
            break;
        case 6 : 
            texte = "Eis-Tempel"; 
            break;
        case 7 : 
            texte = "Verborgener Tempel"; 
            break;
        case 8 : 
            texte = "Schloss Hyrule"; 
            break;

        // 100 -> 199 : Encyclopedie
        case 100 : 
            texte = "MONSTER " + s;
            break;
            
        // 200 -> 299 : Generique
        case 200 :
            texte = "AUSWAHL-SEITE";
            break;
        case 201 : 
            texte = "1.";
            break;
        case 202 :
            texte = "2.";
            break;
        case 203 : 
            texte = "3.";
            break;
        case 204 :
            texte = "OPTIONEN";
            break;
        case 205 :
            texte = "REKORDE";
            break;
        case 206 :
            texte = "OPTIONEN";
            break;
        case 207 :
            texte = "MUSIK";
            break;
        case 208 :
            texte = "TON";
            break;
        case 209 :
            texte = "ZURÜCK";
            break;
        case 210 :
            texte = "REKORDE";
            break;
        case 211 :
            texte = "BEST-ZEIT: " + s;
            break;
        case 212 :
            texte = "TITEL: ERBSENZÄHLER";
            break;
        case 213 :
            texte = "TITEL: ULTIMATIV-HELD";
            break;
        case 214 :
            texte = "TITEL: SUPER-SPRINTER";
            break;
        case 215 :
            texte = "ZURÜCK";
            break;
        case 216 :
            texte = "LÖSCHEN";
            break;
        case 217 :
            texte = "LÖSCHEN ?";
            break;
        case 218 :
            texte = "JA";
            break;
        case 219 :
            texte = "NEIN";
            break;
        case 220 :
            texte = "LADEN";
            break;
        case 221 :
            texte = "LÖSCHEN";
            break;
        case 222 :
            texte = "ABBRUCH";
            break;
        case 223 :
            texte = "HILFE 1/2";
            break;
        case 224 :
#ifdef __vita__
            texte = "Zurück zum Spiel: ¾3 - Nächste S.: ¾5";
#else
            texte = "Zurück zum Spiel: Enter - Nächste S.: Links";
#endif
            break;
        case 225 :
#ifdef __vita__
            texte = "Lesen / Öffnen / Sprechen: ¾2";
#else
            texte = "Lesen / Öffnen / Sprechen: Leertaste";
#endif
            break;
        case 226 :
#ifdef __vita__
            texte = "Bestätigen / Weiter im Text: ¾3";
#else
            texte = "Bestätigen / Weiter im Text: Enter";
#endif
            break;
        case 227 :
#ifdef __vita__
            texte = "Link bewegen: Links ¾9";
#else
            texte = "Link bewegen: Cursortasten";
#endif
            break;
        case 228 :
#ifdef __vita__
            texte = "Rennen : L (halten) / R";
#else
            texte = "Rennen : Umsch. halten oder Feststelltaste";
#endif
            break;
        case 229 :
#ifdef __vita__
            texte = "Schwert benutzen: ¾4";
#else
            texte = "Schwert benutzen: Z oder W";
#endif
            break;
        case 230 :
#ifdef __vita__
            texte = "Rundumschlag: ¾4 halten und loslassen";
#else
            texte = "Rundumschlag: Z oder W halten und loslassen";
#endif
            break;
        case 231 :
#ifdef __vita__
            texte = "Gegenstand wählen: ¾5";
#else
            texte = "Gegenstand wählen: Enter";
#endif
            break;
        case 232 :
#ifdef __vita__
            texte = "Gegenstand benutzen: ¾1";
#else
            texte = "Gegenstand benutzen: X";
#endif
            break;
        case 233 :
#ifdef __vita__
            texte = "Tragen, ohne ausgewählten Handschuh: ¾3";
#else
            texte = "Tragen, ohne ausgewählten Handschuh: C";
#endif
            break;
        case 234 :
#ifdef __vita__
            texte = "Plan ansehen: ¾7 (außen / im Tempel)";
#else
            texte = "Plan ansehen: P (außen oder im Tempel)";
#endif
            break;
        case 235 :
#ifdef __vita__
            texte = "Plan ansehen: L (im Tempel)";
#else
            texte = "Plan ansehen: P (im Tempel)";
#endif
            break;
        case 236 :
#ifdef __vita__
            texte = "Bisher besiegte Monster: ¾6";
#else
            texte = "Bisher besiegte Monster: M";
#endif
            break;
        case 237 :
#ifdef __vita__
            texte = "Sich umsehen: Rechts ¾9";
#else
            texte = "Sich umsehen: Strg und Cursortasten";
#endif
            break;
        case 238 :
#ifdef __vita__
            texte = "Sichern / Beenden: Start";
#else
            texte = "Sichern / Beenden: Esc";
#endif
            break;
        case 239 :
#ifdef __vita__
            texte = "";
#else
            texte = "Vollbild / Fenster: Ctrl und Enter";
#endif
            break;
        case 240 :
            texte = "HILFE 2/2";
            break;
        case 241 :    
#ifdef __vita__
            texte = "Zurück zum Spiel: ¾3 - Vorige S.: ¾7";
#else
            texte = "Zurück zum Spiel: Enter - Vorige S.: Rechts";
#endif
            break;
        case 242 :
#ifdef __vita__
            texte = "Gegenstand benutzen: ¾1";
#else
            texte = "Gegenstand benutzen: X";
#endif
            break;
        case 243 :
#ifdef __vita__
            texte = "Tragen, ohne ausgewählten Handschuh: ¾3"; 
#else
            texte = "Tragen, ohne ausgewählten Handschuh: C"; 
#endif
            break;
        case 244 :
#ifdef __vita__
            texte = "Plan ansehen: ¾7 (außen / im Tempel)";
#else
            texte = "Plan ansehen: P (außen oder im Tempel)";
#endif
            break;
        case 245 :
#ifdef __vita__
            texte = "Plan ansehen: ¾7 (im Tempel)";
#else
            texte = "Plan ansehen: P (im Tempel)";
#endif
            break;
        case 246 :
#ifdef __vita__
            texte = "Bisher besiegte Monster: ¾6";
#else
            texte = "Bisher besiegte Monster: M";
#endif
            break;
        case 247 :
#ifdef __vita__
            texte = "Sich umsehen: Rechts ¾9";
#else
            texte = "Sich umsehen: Strg und Cursortasten";
#endif
            break;
        case 248 :
#ifdef __vita__
            texte = "Sichern / Beenden: Start";
#else
            texte = "Sichern / Beenden: Esc";
#endif
            break;
        case 249 :
#ifdef __vita__
            texte = "";
#else
            texte = "Vollbild / Fenster: Strg und Enter";
#endif
            break;

        case 250 :
            texte = "TITEL: Held von Hyrule";
            break;
        case 251 :
            texte = "TITEL: -nicht geschafft-";
            break;
        case 252 :
            texte = "Alle Aufgaben 100%-ig erfüllt.";
            break;
        case 253 :
            texte = "TITEL: Graf Protz";
            break;
        case 254 :
            texte = "TITEL: -nicht geschafft-";
            break;
        case 255 :
            texte = "Hyrule gerettet, ohne jemals zu";
            break;
        case 256 :
            texte = "sterben, kein Schild genommen,";
            break;
        case 257 :
            texte = "höchstens 10 Leben besitzend,";
            break;
        case 258 :
            texte = "mit keiner Fee gesprochen";
            break;
        case 259 :
            texte = "und keine Flaschen gekauft";
            break;
        case 260 :
            texte = "TITEL: Turbozocker";
            break;
        case 261 :
            texte = "TITEL: -nicht geschafft-";
            break;
        case 262 :
            texte = "Hyrule gerettet in weniger als";
            break;
        case 263 :
            texte = "zwei Stunden!!!";
            break;
        case 264 : 
            texte = "ERGEBNISSE:";
            break;
        case 265 :
            texte = "Spielzeit: " + s;
            break;
        case 266 :
            texte = "Mort " + s + " fois";
            break;
        case 267 :
            texte = "Gestorben: kein mal";
            break;
        case 268 :
            texte = "Herzfragmente: " + s + " / 36";
            break;
        case 269 :
            texte = "Gegenstände: " + s + " / 56";
            break;
        case 270 :
            texte = "Besiegte Arten von Monstern: " + s + " / 46";
            break;
        case 271 :
            texte = "Du hast die Aufgaben zu " + s + "% erfüllt, gratuliere!";
            break;
        case 272 :
            texte = "TITEL : ";
            break;
        case 273 :
            texte = " - ERBSENZÄHLER";
            break;
        case 274 :
            texte = " - ULTIMATIV-HELD";
            break;
        case 275 :
            texte = " - Zelda-Meister";
            break;
        case 276 :
            texte = " - Zelda-Experte";
            break;
        case 277 :
#ifdef __vita__
            texte = " - Zelda-Profi";
#else
            texte = " - Zelda-Profi";
#endif
            break;
        case 278 :
            texte = " - Zelda-Kenner";
            break;
        case 279 :
            texte = " - Zelda-Neuling";
            break;
        case 280 :
            texte = " - Todessüchtiger";
            break;
        case 281 : 
            texte = " - Todesmutiger";
            break;
        case 282 :
            texte = " - SUPER-SPRINTER";
            break;
        case 283 :
            texte = "SPRACHE";
            break;
        case 284 :
            texte = "Deutschen";
            break;

        // 300 -> 399 : Menu
        case 300 :
            texte = "X";
            break;
        case 301 :
            texte = "STATUS:";
            break;
        case 302 :
            texte = "LEBEN   : " + s;
            break;
        case 303 :
            texte = "MAGIE   : " + s;
            break;
        case 304 :
            texte = "KRAFT   : " + s;
            break;
        case 305 :
            texte = "RÜSTUNG : " + s;
            break;
        case 306 :
            texte = "ZEIT    : " + s;
            break;
        case 307 :
            texte = "KRISTALLE:";
            break;

        // 500 -> ?? : Texte
        case 501 : texte = "Du hast ein Schild gefunden!!!**Deine Rüstung steigert sich um einen Punkt!"; break;
#ifdef __vita__
        case 502 : texte = "Du hast ein Schwert gefunden!!!**Du kannst jetzt Monster angreifen (¾4) !!!*Halte ¾4 um den Spezialhieb aufzuladen!!!"; break;
#else
        case 502 : texte = "Du hast ein Schwert gefunden!!!**Du kannst jetzt Monster angreifen (drück Z oder W)!!!*Halte Z um den Spezialhieb aufzuladen!!!"; break;
#endif
        case 503 : texte = "Du hast ein Herzfragment gefunden!!!"; break;
        case 504 : texte = "Noch "+s+" für ein neues Herz nötig!!!"; break;
        case 505 : texte = "Deine Herzanzahl hat sich gerade erhöht!!!"; break;
        case 511 : texte = "N: Link's zu Hause*W: Hyrule-Gebiet*O: Wald-Tempel"; break;
        case 512 : texte = "Berg-Tempel**Nichts für Herzkranke, Angsthasen und Schlappschwänze."; break;
        case 513 : texte = "W: Wüste Gerudo*N: Berg-Tempel"; break;
        case 514 : texte = "N: Berg-Tempel*S: Hyrule Gebiet"; break;
        case 515 : texte = "N: Todesschlucht"; break;
        case 516 : texte = "O: Zum Wald"; break;
        case 517 : texte = "S: See Hylia*O: Spuk-Friedhof"; break;
        case 518 : texte = "S: Zum Dorf Kakariko"; break;
        case 519 : texte = "N: Dorf Kakariko"; break;
        case 520 : texte = "N: Hyrule-Gebiet"; break;
        case 521 : texte = "W: Feuer-Land"; break;
        case 522 : texte = "O: Dorf der Schatten*- Nicht für Lebendige -"; break;
        case 523 : texte = "Dunkler Tempel**Bist du ein Geist, der Arbeit sucht? Dann solltest du dich bei uns melden."; break;
        case 524 : texte = "N: Dorf der Schatten*W: See Hylia"; break;
        case 525 : texte = "N: Spuk-Friedhof**Kein Zutritt"; break;
        case 526 : texte = "Dorf der Schatten"; break;
        case 527 : texte = "Ich verkaufe eine Flasche für 100 Rupien, abgemacht?*               JA ?          nein  "; break;
        case 528 : texte = "Ich verkaufe eine Flasche für 100 Rupien, abgemacht?*               ja            NEIN ?"; break;
        case 529 : texte = "Bedaure, du hast leider nicht genug Rupien"; break;
        case 530 : texte = "Danke, hier ist die Flasche."; break;
        case 531 : texte = "Komm wieder, falls sich deine Meinung geändert hat."; break;
        case 532 : texte = "Das war leider meine einzige Flasche."; break;
        case 533 : texte = "Du hast eine leere Flasche gekauft!!!**Darin kannst du Getränke aufbewahren!!!"; break;
        case 535 : texte = "Die Einwohner dieses Dorfes sprechen einen ungewöhnlichen Dialekt, nix versteh'n..."; break;
        case 536 : texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 537 : texte = "Falls du wirklich hier hindurch willst, musst du erst den Dorfältesten fragen!!!"; break;
        case 538 : texte = "Der Dorfälteste erlaubt dir also zu passieren??? Grrrr... Dann geh doch!!!"; break;
        case 539 : texte = "Geh mir aus dem Weg!!!"; break;
        case 540 : texte = "Normalerweise kommen keine Touristen hier her."; break;
        case 541 : texte = "Einheimische Monster fürchten sich kaum vor etwas. Zum Glück überfallen sie nur Menschen."; break;
        case 542 : texte = "Wirklich?*Verstehst du, was ich sage?"; break;
        case 543 : texte = "N: Wüste und Dorf Gerudo"; break;
        case 544 : texte = "S: See Hylia*W: Schloss Hyrule"; break;
        case 545 : texte = "Dorf Kakariko"; break;
        case 546 : texte = "W: Schloss Hyrule"; break;
        case 547 : texte = "Was für ein schöner Tag!!!"; break;
        case 548 : texte = "Aber warum soll ich auf dieses Viehzeug aufpassen???*Ich hasse Hühner!!!"; break;
        case 549 : texte = "Im Dorfladen kannst du viele nützliche Dinge kaufen."; break;
        case 550 : texte = "S: Dorf Kakariko*W: Wüste Gerudo*O: Todesschlucht"; break;
        case 551 : texte = "Dorf Gerudo"; break;
        case 552 : texte = "Verirrt in der Wüste?*Du bist hier:*                        X"; break;
        case 554 : texte = "S: Zum Schloss Hyrule"; break;
        case 555 : texte = "Wüsten-Tempel**Tritt ein für ein Bad.*(Das Wasser ist nicht zum Trinken da!)"; break;
        case 556 : texte = "Wald-Tempel**Schütze die Bäume, fang die Biber!!!"; break;
        case 557 : texte = "See-Tempel**Badekappen vorgeschrieben!"; break;
        case 558 : texte = "Eis-Tempel**Das Personal möchte dich daran erinnern, dass ein Tempel keine Eissporthalle ist."; break;
        case 559 : texte = "Warst du schon beim Dorfschmied?*Man sagt, er sei sehr begabt, die Ausrüstung für Abenteurer aufzuwerten. Er hat viele Kunden."; break;
        case 560 : texte = "Der Tempel ist in der tiefsten Wüste, in einer antiken Oase."; break;
        case 561 : texte = "S: Feuerland*O: Dorf Kakariko"; break;
        case 562 : texte = "Schloss Hyrule"; break;
        case 563 : texte = "O: Dorf Kakariko"; break;
        case 564 : texte = "W: Schildkrötfelsen*O: See Hylia"; break;
        case 565 : texte = "Geheim-Tempel**Hier ruht das Schwert Excalibur."; break;
        case 566 : texte = "N: Zum Spuk-Friedhof"; break;
#ifdef __vita__
        case 567 : texte = "Du hast den Tempelplan gefunden!!!*Drück ¾7, um den Plan anzusehen."; break;
#else
        case 567 : texte = "Du hast den Tempelplan gefunden!!!*Drück P, um den Plan anzusehen."; break;
#endif
        case 568 : texte = "Du hast den Kompass gefunden!!!*Du kannst nun den Boss und die Truhen auf dem Plan sehen."; break;
        case 569 : texte = "Du hast den Boss-Schlüssel gefunden!!!"; break;
        case 570 : texte = "Du hast einen Schlüssel gefunden!!!*Geh auf eine Tür zu, um diese zu öffnen."; break;
#ifdef __vita__
        case 571 : texte = "Du hast die magischen Handschuhe gefunden!!!*Benutz diese (oder drück ¾3) zum Heben/Schieben schwerer Objekte."; break;
#else        
        case 571 : texte = "Du hast die magischen Handschuhe gefunden!!!*Benutz diese (oder drück C) zum Heben/Schieben schwerer Objekte."; break;
#endif        
        case 572 : texte = "Du hast einen Kristall gefunden!!!"; break;
        case 573 : texte = "Für was mag der wohl gut sein...?"; break;
        case 574 : texte = "Es müssen noch "+s+" gefunden werden!!!"; break;
        case 575 : texte = "Nur noch 2 Exemplare fehlen noch!!!"; break;
        case 576 : texte = "Jetzt fehlt nur noch einer!!!"; break;
        case 577 : texte = "Du hast jetzt alle 7 Kristalle. Lauf schnell zum Schloss und rette Zelda!!!"; break;
        case 580 : texte = "Du hast einen Hakenwerfer gefunden!!!*Damit kannst du einige Hindernisse überwinden."; break;
        case 581 : texte = "Du hast die magische Laterne gefunden!!!*Damit kannst du Feuer entfachen."; break;
        case 582 : texte = "Du hast Schwimmflossen gefunden!!!*Damit kannst du endlich im See baden gehen."; break;
        case 583 : texte = "Du hast einen Hammer gefunden!!!*Damit kannst du Hindernisse zu Brei schlagen."; break;
        case 584 : texte = "Du hast den magischen Feuerstab gefunden!!!*Damit kannst du mächtige Feuerbälle schleudern."; break;
        case 585 : texte = "Du hast den magischen Eisstab gefunden!!!*Damit kannst du etwas beliebiges Einfrieren."; break;
        case 586 : texte = "Du hast das Schwert Excalibur gefunden!!!*Selbst Ganon kann nicht seiner Macht standhalten!!! (theoretisch)"; break;
        case 587 : texte = "Endlich Link, du hast mich befreit!!!**Lass uns schnell Ganon finden. Wir müssen unbedingt das Triforce zurück bekommen!"; break;
        case 589 : texte = "Der Geheimgang hinter dem Thron führt zu Ganon. Beeil dich!"; break;
        case 590 : texte = "Wir sind nahe dran, folge mir!"; break;
        case 591 : texte = "Ich befürchte, dass du mit den gegenwärtigen Waffen Ganon nicht besiegen kannst...*Geh nach Karariko und sprich mit dem Dorfältesten. Er findet sicher eine Lösung."; break;
        case 592 : texte = "Ganon ist hinter dieser Tür da.*Ich habe soeben alle deine Wunden geheilt!"; break;
        case 593 : texte = "Ganon ist irgendwo hier im Schloss."; break;
        case 594 : texte = "Du solltest auf Prinzessin Zelda warten!!!"; break;
        case 595 : texte = "Würdest du nicht dieses mulmige Gefühl manchmal loswerden wollen???"; break;
        case 596 : texte = "Zelda wartet auf dich!!!"; break;
        case 597 : texte = "Du hast das Triforce gefunden!!!"; break;
        case 598 : texte = "Du hast das Buch Mudora gefunden!!!**Jetzt kannst du endlich die Sprache der antiken Hylian verstehen!!!"; break;
        case 599 : texte = "Du hast mich gefunden, Link. Zur Belohnung schenke ich dir das Din-Amulett. Dies steigert deine Rüstung um einen Punkt."; break;
        case 600 : texte = "Du hast mich gefunden, Link. Zur Belohnung schenke ich dir das Nayru-Amulett. Dies steigert deine Rüstung um zwei Punkte!!!"; break;
        case 601 : texte = "..."; break;
        case 602 : texte = "Du hast ein magisches Amulett bekommen!!!**Dies steigert deine Rüstung!!!"; break;
        case 603 : texte = "Du hast mich gefunden, Link. Zur Belohnung werde ich deine Zauberkraft verdoppeln!!!"; break;
        case 604 : texte = "Deine Zauberkraft hat sich verdoppelt!!!"; break;
        case 605 : texte = "Komm wieder, wenn du eine leere Flasche hast, dann verkauf ich dir einen roten Trank, der alle Wunden heilt."; break;
        case 606 : texte = "Den roten Heiltrank für 60 Rupien, abgemacht?*               JA ?          nein  "; break;
        case 607 : texte = "Den roten Heiltrank für 60 Rupien, abgemacht?*               ja            NEIN ?"; break;
        case 608 : texte = "Danke. Hier ist der Trank.";break;
        case 609 : texte = "Du hast einen roten Trank bekommen!!!*(Stellt die volle Gesundheit wieder her)"; break;
        case 610 : texte = "Du hast einen grünen Trank bekommen!!!*(Stellt die magischen Kräfte wieder her)"; break;
        case 611 : texte = "Du hast einen blauen Trank bekommen!!!*(Stellt volle Gesundheit und die magischen Kräfte wieder her)"; break;
        case 612 : texte = "Hallo, was möchtest du gerne trinken?"; break;
        case 613 : texte = "-Hick!- Eine Fee flüsterte mir ins Ohr... -Hick!- ...derjenige, der mich findet, bekommt etwas besonderes... -Hick!!!-"; break;
        case 614 : texte = "Ein Herz für 10 Rupien, abgemacht?**               JA ?          nein  "; break;
        case 615 : texte = "Ein Herz für 10 Rupien, abgemacht?**               ja            NEIN ?"; break;
        case 616 : texte = "Kleiner Zaubertrank für 20 Rupien, abgemacht?**               JA ?          nein  "; break;
        case 617 : texte = "Kleiner Zaubertrank für 20 Rupien, abgemacht?**               ja            NEIN ?"; break;
        case 618 : texte = "Großer Zaubertrank für 30 Rupien, abgemacht?**               JA ?          nein  "; break;
        case 619 : texte = "Großer Zaubertrank für 30 Rupien, abgemacht?**               ja            NEIN ?"; break;
        case 620 : texte = "5 Pfeile für 30 Rupien, abgemacht?**               JA ?          nein  "; break;
        case 621 : texte = "5 Pfeile für 30 Rupien, abgemacht?**               ja            NEIN ?"; break;
        case 622 : texte = "Eine Bombe für 30 Rupien, abgemacht?**               JA ?          nein  "; break;
        case 623 : texte = "Eine Bombe für 30 Rupien, abgemacht?**               ja            NEIN ?"; break;
        case 624 : texte = "Ein Bogen für 1000 Rupien, abgemacht?**               JA ?          nein  "; break;
        case 625 : texte = "Ein Bogen für 1000 Rupien, abgemacht?**               ja            NEIN ?"; break;
        case 626 : texte = "Ein Bogen für 50 Rupien, abgemacht?**               JA ?          nein  "; break;
        case 627 : texte = "Ein Bogen für 50 Rupien, abgemacht?**               ja            NEIN ?"; break;
        case 628 : texte = "Das brauchst du jetzt nicht."; break;
        case 629 : texte = "Danke."; break;
        case 630 : texte = "Du hast den Bogen bekommen!!!*Damit kannst du auf entfernte Ziele schießen."; break;
        case 631 : texte = "Wähle, was du begehrst."; break;
        case 632 : texte = "Was???*Du hast einen Auftrag vom Dorfältesten???*Nun gut, dann gebe ich dir einen Preisnachlass auf den Bogen."; break;
        case 633 : texte = "Hallo Link. Ich bin der Dorfälteste. Ich dachte mir schon, dass du zu mir kommen wirst."; break;
        case 634 : texte = "Seit heute früh treiben sich Monster in Hyrule herum. Ich versuchte darüber mit Zelda zu sprechen, aber wie du bereits sagtest, blockiert ein Zauberbann den Eingang zum Schloss..."; break;
        case 636 : texte = "Du sagst, Ganon sei Schuld für all dies? Er soll das Triforce gestohlen und Prinzessin Zelda gefangen halten?"; break;
        case 637 : texte = "Mmmm... Die Situation ist ernster, als ich dachte..."; break;
        case 638 : texte = "Wir müssen rasch handeln. Du musst erneut gegen Ganon kämpfen!"; break;
        case 639 : texte = "Wie kommt man ins Schloss? Ich hätte da eine Idee..."; break;
        case 640 : texte = "Wie bekannt, wurden die Kräfte der 7 Weisen von Zauberer Aghanim in 7 Kristalle gesperrt, als er versuchte den Pfad zur Dunklen Welt zu öffnen, wo Ganon sich aufhält."; break;
        case 641 : texte = "Jetzt, nachdem du Ganon besiegt, das Triforce gefunden und damit die 7 Weisen wiederbelebt hast, haben diese Kristalle ihre magischen Kräfte immer noch erhalten."; break;
        case 642 : texte = "Sie sind tief im Inneren der 7 Tempel versteckt worden. Hol sie dir alle, dann kannst du Ganon's Zauberbann am Schlosseingang lösen."; break;
        case 643 : texte = "Das wird jedoch nicht einfach werden, denn Ganon hat sicher seine besten Einheiten zum Schutz dieser Kristalle eingesetzt..."; break;
        case 644 : texte = "Zu guter Letzt: Du wirst mit deiner jetzigen Ausrüstung nicht weit kommen. Geh zum Waffenhändler und sage ihm, dass du in meinem Auftrag kommst. Er wird sich dann wohl erkenntlich zeigen."; break;
        case 645 : texte = "Geh zum Waffenhändler und sage ihm, dass du in meinem Auftrag kommst! Er wird sich dann wohl erkenntlich zeigen."; break;
        case 646 : texte = "Du brauchst alle 7 Kristalle, um Zelda und Hyrule retten zu können."; break;
        case 647 : texte = "Du besitzt alle 7 Kristalle? Geh nun geradewegs zum Schloss und befrei' erst die Prinzessin. Sie wird besser als ich wissen, wie Hyrule gerettet werden kann."; break;
        case 648 : texte = "Sind deine Waffen gegen Ganon null und nichtig? Deswegen musst du das Schwert Excalibur finden. Man sagt, es sei gut versteckt in einem Geheim-Tempel.*Nebenbei: Der Weg zum Schwert Excalibur führt mitten durch ein Dorf, nur von Monstern bewohnt... Ich frag mich, ob es so ein Dorf gibt..."; break;
        case 650 : texte = "Nun, ich befürchte dass deine Ausrüstung unzulänglich ist, um diesen Tempel zu erreichen. Du solltest zum Schmied von Gerudo gehen..."; break;
        case 651 : texte = "Es ist jetzt an der Zeit, Ganon ins Auge zu blicken und ihm das Triforce abzunehmen!"; break;
        case 652 : texte = "Heh! Du musst erst bezahlen, wenn du eine meiner Truhen öffnen willst!!!"; break;
        case 653 : texte = "Eine dieser Truhen enthält ein Herzfragment. Willst du für 10 Rupien dein Glück versuchen? Du darfst nur eine Truhe öffnen, abgemacht?*                JA ?          nein"; break;
        case 654 : texte = "Eine dieser Truhen enthält ein Herzfragment. Willst du für 10 Rupien dein Glück versuchen? Du darfst nur eine Truhe öffnen, abgemacht?*                ja            NEIN ?"; break;
        case 655 : texte = "Wähle eine Truhe."; break;
        case 656 : texte = "Ich habe leider keine Preise mehr für dieses Spiel, bedaure."; break;
        case 657 : texte = "Du hast verloren! Diese Truhe war leer. Versuch es noch einmal!"; break;
        case 658 : texte = "Hallo! Falls du den Schmied suchst, er wohnt etwas abseits."; break;
        case 659 : texte = "Hallo Link, ich bin der Dorfälteste hier.*Du solltest zum Schmied gehen und ihm zeigen, was du brauchst, damit er deine Ausrüstung verbessern kann."; break;
        case 660 : texte = "Ich kannte dein Anliegen schon, deshalb habe ich bereits mit ihm gesprochen.*Alles wird für dich kostenlos erledigt."; break;
        case 661 : texte = "Du brauchst diesen Trank jetzt nicht zu benutzen."; break;
        case 662 : texte = "Grüner Zaubertrank für 40 Rupien, einverstanden?*               JA ?          nein  "; break;
        case 663 : texte = "Grüner Zaubertrank für 40 Rupien, einverstanden?*               ja            NEIN ?"; break;
        case 664 : texte = "Komm wieder, wenn du eine leere Flasche hast, dann verkauf ich dir einen grünen Trank, welcher die Zauberkraft wiederherstellt."; break;
        case 665 : texte = "Komm später wieder, ich bin zu sehr beschäftigt!"; break;
        case 666 : texte = "Kann ich etwas für dich tun?"; break;
        case 667 : texte = "Soll ich dein Schwert härten?**               JA ?          nein  "; break;
        case 668 : texte = "Soll ich dein Schwert härten?**               ja            NEIN ?"; break;
        case 669 : texte = "Dein Schwert hat seine Kraft verdreifacht. Außerdem kann es jetzt magische Hiebe schleudern, da guckst du!!!*"; break;
        case 670 : texte = "Soll ich deine Handschuhe aufwerten?**               JA ?          nein  "; break;
        case 671 : texte = "Soll ich deine Handschuhe aufwerten?**               ja            NEIN ?"; break;
        case 672 : texte = "Die Kraft deiner Handschuhe ermöglicht dir nun, schwere Brocken zu heben."; break;
        case 673 : texte = "Soll ich deinen Bogen aufwerten?**               JA ?          nein  "; break;
        case 674 : texte = "Soll ich deinen Bogen aufwerten?**               ja            NEIN ?"; break;
        case 675 : texte = "Dein Bogen verwendet nun Silberpfeile mit kataklystischer Energie!!!"; break;
        case 676 : texte = "Komm wieder, wenn du eine leere Flasche hast, dann verkauf ich dir den blauen Trank, der Gesundheit und Zauberkraft wiederherstellt."; break;
        case 677 : texte = "Der blaue Zaubertrank für 160 Rupien, einverstanden?*               JA ?          nein  "; break;
        case 678 : texte = "Der blaue Zaubertrank für 160 Rupien, einverstanden?*               ja            NEIN ?"; break;
        case 679 : texte = "Unser Dorfältester hat festgelegt, unvorsichtige Abenteurer vom Tempel fernzuhalten. Ich erlaube niemandem zu passieren."; break;
        case 680 : texte = "Mmmm... Du hast bereits 4 Kristalle gefunden?*Ich muss zugeben, dass du mich beeindruckst..."; break;
        case 681 : texte = "Nun gut, du darfst das Gräberfeld überqueren, aber auf eigenes Risiko."; break;
        case 682 : texte = "Sag dem Wächter im Norden des Dorfes, dass er dich durchlassen soll."; break;
        case 683 : texte = "Ach soo, du lebst immer noch...*Erstaunlich."; break;
        case 684 : texte = "Der Dunkle Tempel ist der Startpunkt des Weges zum Erreichen eines legendären Objektes. Dieses Dorf existiert nur deshalb, um Abenteurer davon fern zu halten."; break;
        case 685 : texte = "Du hast also das Schwert Excalibur gefunden?*Aber glaub' nicht, dass du es für immer behalten kannst."; break;
        case 686 : texte = "Das Schwert Excalibur ist eines der wertvollsten Kulturgüter von Hyrule, zusammen mit dem Triforce. Du wirst es am Ende deiner Mission in den Altarraum zurück legen!"; break;
        case 687 : texte = "Alle Bewohner dieses Dorfes sind Geister, die Prinzessin Zelda's Anweisungen treu befolgen."; break;
        case 688 : texte = "Als der Frieden in Hyrule wieder einzog und die Lichtwelt mit dem Goldenen Land wieder vereinigt war, bat Zelda (heimlich) einige Geister diese Stadt zu errichten,"; break;
        case 689 : texte = "um den Zugang zu einem sehr wertvollen Objekt zu blockieren."; break;        
        case 690 : texte = "Willkommen Link!*Lass mich dir erklären, was ich hier mache."; break;
        case 691 : texte = "Wie du sicher bemerkt hast, sind Monster in Hyrule aufgetaucht. Es ist das erste mal, seit deinem Sieg über Ganon, dass ich Monster beobachte."; break;
        case 692 : texte = "Nun habe ich beschlossen, alle Monster zu katalogisieren."; break;
        case 693 : texte = "Unglücklicherweise bin ich wirklich zu ängstlich, diesen persönlich zu begegnen. Deshalb brauche ich deine Hilfe."; break;
        case 694 : texte = "Du musst jede unbekannte Monster-Art besiegen und mir im Anschluss davon berichten."; break;
        case 695 : texte = "Jedes mal, wenn du 7 neue Arten von Monstern besiegt hast, gebe ich dir ein Herzfragment dafür."; break;
#ifdef __vita__
        case 696 : texte = "Willst du wissen, welche Monster du bereits besiegt hast, dann drück ¾6"; break;
#else
        case 696 : texte = "Willst du wissen, welche Monster du bereits besiegt hast, dann drück M."; break;
#endif
        case 697 : texte = "Abermals "+s+" unbekannte Monster bis zur nächsten Belohnung."; break;
        case 698 : texte = "Du benötigst nur noch ein unbekanntes Monster bis zur nächsten Belohnung!!!"; break;
        case 699 : texte = "Nimm dieses Geschenk für deine tatkräftige Unterstützung meines Projekts:"; break;
        case 700 : texte = "Tut mir leid, aber ich habe keine Geschenke mehr für dich..."; break;
        case 701 : texte = "Ich kann es nicht fassen. Dir gelang es, alle Monster-Arten zu besiegen!!!*Gratulation, Link!!!"; break;        
        case 702 : texte = "                    Level 1:**                  Wald-Tempel"; break;
        case 703 : texte = "                    Level 2:**                 Wasser-Tempel"; break;
        case 704 : texte = "                    Level 3:**                  Berg-Tempel"; break;
        case 705 : texte = "                    Level 4:**                 Wüsten-Tempel"; break;
        case 706 : texte = "                    Level 5:**                 Dunkler Tempel"; break;
        case 707 : texte = "                    Level 6:**                  Feuer-Tempel"; break;
        case 708 : texte = "                    Level 7:**                   Eis-Tempel"; break;
        case 709 : texte = "                    Level ?:**                 Geheim-Tempel"; break;
        case 710 : texte = "                 Letzter Level:**                 Schloss Hyrule"; break;        
        case 711 :texte = "                  Schon müde?                   ?               WEITER MACHEN               ?               Sichern und beenden                          Beenden ohne zu sichern           "; break;
        case 712 :texte = "                  Schon müde?                                   weiter machen                  ?            SICHERN UND BEENDEN            ?             Beenden ohne zu sichern           "; break;
        case 713 :texte = "                  Schon müde?                                   weiter machen                               Sichern und beenden               ?          BEENDEN OHNE ZU SICHERN          ?"; break;
        case 714 : texte = "Als Link das Triforce berührte, verschwanden auch alle Monster und Frieden zog ein.**"
          "Dann fasste Prinzessin Zelda einen mutigen Entschluss: Sie berührte kreisend das Triforce und wünschte sich etwas.**"
          "Das Triforce hat schon genug Probleme im Königreich verursacht. Früher oder später wird erneut ein Bösewicht das Triforce finden.**"
          "Im gleichen Moment, als die Prinzessin die Reliquie berührte, verschwand diese für immer von Hyrule.";
        case 715 : texte = "Seit diesem Tag lebten die Bewohner von Hyrule in Frieden, ohne Angst vor neuem Unheil.**"
          "Deshalb ist die Geschichte von Zelda, dem Triforce und dem Goldenen Land Hyrule hiermit beendet.**"
          "Das Schwert Excalibur gilt als sicher verwahrt (-irgendwo an einem geheimen Ort-) und ist Link's jüngstes Beutestück..."; break;
        case 716 : texte = "Du hast mich gefunden, Link. Zur Belohnung schenke ich dir das Farore-Amulett. Dies steigert deine Rüstung um einen Punkt..."; break;
        case 717 : texte = "Möchtest du dein Spiel sichern?**                    ?  JA  ?*                      nein  "; break;
        case 718 : texte = "Möchtest du dein Spiel sichern?**                       ja   *                    ? NEIN ?"; break;
        case 719 : texte = "Spielstand gesichert."; break;
        case 720 : texte = "Das Königreich Hyrule lebte in Frieden, seit Link, der letzte Ritter von Hyrule, den heimtückischen Ganon besiegte und das wertvolle Triforce von ihm zurückgewann."; break;
        case 721 : texte = "Niemand kennt die Worte von Link's Wunsch an das Triforce, allerdings hat dieser die Wiedervereinigung der Hellen mit der Dunklen Welt bewirkt, sowie *die Auferstehung der 7 Weisen."; break;
        case 722 : texte = "Schließlich übergab Link das Triforce und das Schwert Excalibur an Prinzessin Zelda, und die Leute begannen zu glauben, dass nun für immer Frieden herrschen wird.                        Aber die Leute lagen falsch..."; break;
        case 723 : texte = "... denn unglücklicherweise hatte Link's Wunsch auch negative Auswirkungen. Ganon und seine Schergen sind wiederauferstanden und machen sich kampfbereit."; break;
        case 724 : texte = "Irgendwo im Wald von Hyrule schläft Link und ahnt noch nicht, dass Ganon bereits den Kampf begonnen hat,"; break;
        case 725 : texte ="bis eine wohlbekannte Stimme zu ihm spricht, während er weiter fest schläft..."; break;
        case 726 : texte = "Hilf mir!*Hilf mir!*Ich bin's, Zelda!*Ich spreche zu dir über Telepathie."; break;
        case 727 : texte = "Ich bin Gefangene im Kerker des Schlosses!*Ich brauche deine Hilfe!*Ganon ist zurückgekehrt, und er hat bestimmt schon das Triforce gefunden..."; break;
        case 728 : texte = "Komm schnell zu mir ins Schloss, Link, du bist meine einzige Hoffnung..."; break;
#ifdef __vita__
        case 729 : texte = "Brauchst du HILFE, dann drück Select"; break;
#else
        case 729 : texte = "Brauchst du HILFE, dann drück F1."; break;
#endif
        default : 
            texte = "FALSH TEXT";
    }

    return texte;
}

std::string Texte::getTexteES(int id, std::string s){
    std::string texte = "";
    switch(id) {
        // 0 -> 99 : Carte
        case 0 : 
            texte = "Templo del Bosque"; 
            break;
        case 1 : 
            texte = "Templo del Agua"; 
            break;
        case 2 : 
            texte = "Templo de la Montaña";
            break;
        case 3 : 
            texte = "Templo del Desierto"; 
            break;
        case 4 : 
            texte = "Templo de las Tinieblas"; 
            break;
        case 5 : 
            texte = "Templo del Fuego"; 
            break;
        case 6 : 
            texte = "Templo de Hielo"; 
            break;
        case 7 : 
            texte = "Templo Oscuro"; 
            break;
        case 8 : 
            texte = "Castillo de Hyrule"; 
            break;

        // 100 -> 199 : Encyclopedie
        case 100 : 
            texte = "MONSTRUOS " + s;
            break;
            
        // 200 -> 299 : Generique
        case 200 :
            texte = "PANTALLA DE SELECCION";
            break;
        case 201 : 
            texte = "1.";
            break;
        case 202 :
            texte = "2.";
            break;
        case 203 : 
            texte = "3.";
            break;
        case 204 :
            texte = "OPCIONES";
            break;
        case 205 :
            texte = "RECORDS";
            break;
        case 206 :
            texte = "OPCIONES";
            break;
        case 207 :
            texte = "MUSICA";
            break;
        case 208 :
            texte = "SONIDOS";
            break;
        case 209 :
            texte = "ANTERIOR";
            break;
        case 210 :
            texte = "RECORDS";
            break;
        case 211 :
            texte = "MEJOR TIEMPO : " + s;
            break;
        case 212 :
            texte = "RANGO DE LOS 100%";
            break;
        case 213 :
            texte = "RANGO ULTIMO";
            break;
        case 214 :
            texte = "RANGO DE RAPIDEZ";
            break;
        case 215 :
            texte = "ANTERIOR";
            break;
        case 216 :
            texte = "BORRAR";
            break;
        case 217 :
            texte = "BORRAR ?";
            break;
        case 218 :
            texte = "SI";
            break;
        case 219 :
            texte = "NO";
            break;
        case 220 :
            texte = "CARGAR";
            break;
        case 221 :
            texte = "BORRAR";
            break;
        case 222 :
            texte = "ANULAR";
            break;
        case 223 :
            texte = "AYUDA 1/2";
            break;
        case 224 :
#ifdef __vita__
            texte = "Volver al juego : ¾3 - Siguiente : ¾5";
#else
            texte = "Volver al juego : Enter - Siguiente : Derecha";
#endif
            break;
        case 225 :
#ifdef __vita__
            texte = "Leer / Abrir / Hablar : ¾2";
#else
            texte = "Leer / Abrir / Hablar : Espacio: Espace";
#endif
            break;
        case 226 :
#ifdef __vita__
            texte = "Validar / Pasar texto : ¾3";
#else
            texte = "Validar / Pasar texto : Enter";
#endif
            break;
        case 227 :
#ifdef __vita__
            texte = "Mover a Link : ¾9 Izquierda";
#else
            texte = "Mover a Link : Flechas de dirección";
#endif
            break;
        case 228 :
#ifdef __vita__
            texte = "Correr : L (mantenido) / R";
#else
            texte = "Correr : Mayus mantenido o Capslock";
#endif
            break;
        case 229 :
#ifdef __vita__
            texte = "Golpe de espada : ¾4";
#else
            texte = "Golpe de espada : Z o W";
#endif
            break;
        case 230 :
#ifdef __vita__
            texte = "Giratorio : ¾4 mantenido luego soltado";
#else
            texte = "Giratorio : Z o W mantenido luego soltado";
#endif
            break;
        case 231 :
#ifdef __vita__
            texte = "Menu de selección del objeto : ¾5";
#else
            texte = "Menu de selección del objeto : Enter";
#endif
            break;
        case 232 :
#ifdef __vita__
            texte = "Utilizar el objeto seleccionnado : ¾1";
#else
            texte = "Utilizar el objeto seleccionnado : X";
#endif
            break;
        case 233 :
#ifdef __vita__
            texte = "Levantar sin equipar los guantes : ¾3";
#else
            texte = "Levantar sin equipar los guantes : C";
#endif
            break;
        case 234 :
#ifdef __vita__
            texte = "AVer el mapa : ¾7 (exterior/templos)";
#else
            texte = "AVer el mapa : P (exterior/templos)";
#endif
            break;
        case 235 :
#ifdef __vita__
            texte = "Ver el mapa : L (en los templos)";
#else
            texte = "Ver el mapa : P (en los templos)";
#endif
            break;
        case 236 :
#ifdef __vita__
            texte = "Ver los monstros vencidos : ¾6";
#else
            texte = "Ver los monstros vencidos : M";
#endif
            break;
        case 237 :
#ifdef __vita__
            texte = "Mirar alrededor : ¾9 Derecha";
#else
            texte = "Mirar alrededor : Ctrl y dirección";
#endif
            break;
        case 238 :
#ifdef __vita__
            texte = "Grabar / Quitar : Start";
#else
            texte = "Grabar / Quitar : Esc";
#endif
            break;
        case 239 :
#ifdef __vita__
            texte = "";
#else
            texte = "Agrandar / Encoger : Ctrl y Enter";
#endif
            break;
        case 240 :
            texte = "AYUDA 2/2";
            break;
        case 241 :    
#ifdef __vita__
            texte = "Volver al juego : ¾3 - Anterior : ¾7";
#else
            texte = "Volver al juego : Enter - Anterior : Izquierda";
#endif
            break;
        case 242 :
#ifdef __vita__
            texte = "Utilizar el objeto seleccionnado : ¾1";
#else
            texte = "Utilizar el objeto seleccionnado : X";
#endif
            break;
        case 243 :
#ifdef __vita__
            texte = "Levantar sin equipar los guantes : ¾3"; 
#else
            texte = "Levantar sin equipar los guantes : C"; 
#endif
            break;
        case 244 :
#ifdef __vita__
            texte = "Ver el mapa : ¾7 (exterior/templos)";
#else
            texte = "Ver el mapa : P (exterior o templos)";
#endif
            break;
        case 245 :
#ifdef __vita__
            texte = "Ver el mapa : ¾7 (en los templos)";
#else
            texte = "Ver el mapa : P (en los templos)";
#endif
            break;
        case 246 :
#ifdef __vita__
            texte = "Ver los monstruos vencidos : ¾6";
#else
            texte = "Ver los monstruos vencidos : M";
#endif
            break;
        case 247 :
#ifdef __vita__
            texte = "Mirar alrededor : ¾9 Derecha";
#else
            texte = "Mirar alrededor : Ctrl y dirección";
#endif
            break;
        case 248 :
#ifdef __vita__
            texte = "Grabar / Quitar : Start";
#else
            texte = "Grabar / Quitar : Esc";
#endif
            break;
        case 249 :
#ifdef __vita__
            texte = "";
#else
            texte = "Agrandar / Encoger : Ctrl y Enter";
#endif
            break;

        case 250 :
            texte = "RANGO : Héroe de Hyrule";
            break;
        case 251 :
            texte = "RANGO : DESCONOCIDO";
            break;
        case 252 :
            texte = "Acabar el juego a 100%";
            break;
        case 253 :
            texte = "RANGO : Chulo";
            break;
        case 254 :
            texte = "RANGO : DESCONOCIDO";
            break;
        case 255 :
            texte = "Acabar el juego sin morir,";
            break;
        case 256 :
            texte = "con 10 corazones como máximo,";
            break;
        case 257 :
            texte = "sin hablar a las Grandes Hadas,";
            break;
        case 258 :
            texte = "sin comprar botellas";
            break;
        case 259 :
            texte = "y sin coger el escudo.";
            break;
        case 260 :
            texte = "RANGO : Corredor de Hyrule";
            break;
        case 261 :
            texte = "RANGO : DESCONOCIDO";
            break;
        case 262 :
            texte = "Acabar el juego en menos de";
            break;
        case 263 :
            texte = "dos horas";
            break;
        case 264 : 
            texte = "RESULTADOS :";
            break;
        case 265 :
            texte = "Tiempo jugando : " + s;
            break;
        case 266 :
            texte = "Muerto " + s + " veces";
            break;
        case 267 :
            texte = "Muerto " + s + " veces";
            break;
        case 268 :
            texte = "Cuarto de corazón : " + s + " / 36";
            break;
        case 269 :
            texte = "Objetos : " + s + " / 56";
            break;
        case 270 :
            texte = "Tipos de enemigos vencidos : " + s + " / 46";
            break;
        case 271 :
            texte = "Has acabado este juego al " + s + "%, felicitaciones !";
            break;
        case 272 :
            texte = "RANGO : ";
            break;
        case 273 :
            texte = " - Chulo";
            break;
        case 274 :
            texte = " - Héroe de Hyrule";
            break;
        case 275 :
            texte = " - Perfeccionista";
            break;
        case 276 :
            texte = " - Fan de Zelda";
            break;
        case 277 :
#ifdef __vita__
            texte = " - Genio del teclado";
#else
            texte = " - Genio del teclado";
#endif
            break;
        case 278 :
            texte = " - Veterano";
            break;
        case 279 :
            texte = " - Principiante";
            break;
        case 280 :
            texte = " - Muerto en vida";
            break;
        case 281 : 
            texte = " - Kamikaze";
            break;
        case 282 :
            texte = " - Corredor de Hyrule";
            break;
        case 283 :
            texte = "IDIOMA";
            break;
        case 284 :
            texte = "Español";
            break;

        // 300 -> 399 : Menu
        case 300 :
            texte = "X";
            break;
        case 301 :
            texte = "ESTATUTO :";
            break;
        case 302 :
            texte = "VIDA       : " + s;
            break;
        case 303 :
            texte = "MAGIA     : " + s;
            break;
        case 304 :
            texte = "FUERZA     : " + s;
            break;
        case 305 :
            texte = "DEFENSA   : " + s;
            break;
        case 306 :
            texte = "TIEMPO     : " + s;
            break;
        case 307 :
            texte = "CRISTALES :";
            break;

        // 500 -> ?? : Texte
        case 501 : texte = "Has encontrado un escudo !!!**Tu defensa aumenta de un punto!"; break;
#ifdef __vita__
        case 502 : texte = "Has encontrado una espada !!!**Ahora puedes defenderte contra los monstros con la tecla ¾4 !!!*Manten ¾4 para descargar el giratorio !"; break;
#else
        case 502 : texte = "Has encontrado una espada !!!**Ahora puedes defenderte contra los monstros con la tecla Z (o W) !!!*Manten Z para descargar el giratorio !"; break;
#endif
        case 503 : texte = "Has encontrado un cuarto de corazón !!!"; break;
        case 504 : texte = "Con "+s+" mas obtendras un corazón adicional !!!"; break;
        case 505 : texte = "Tu numero de corazónes acaba de aumentar !!!"; break;
        case 511 : texte = "N : Casa de Link*O : Finca de Hyrule*E : Templo del Bosque"; break;
        case 512 : texte = "Templo de la Montaña**No aconsejado para cardiacos, miedosos, y emotivos en general."; break;
        case 513 : texte = "O : Entrada del desierto*N : Templo de la Montaña"; break;
        case 514 : texte = "N : Templo de la Montaña*S : Finca de Hyrule"; break;
        case 515 : texte = "N : Montaña de la Muerte"; break;
        case 516 : texte = "E : Entrada del Bosque"; break;
        case 517 : texte = "S : Lago de Hylia*E : Cementerio de los Espíritus"; break;
        case 518 : texte = "S : Hacia el pueblo Kakariko"; break;
        case 519 : texte = "N : Pueblo Kakariko"; break;
        case 520 : texte = "N : Finca de Hyrule"; break;
        case 521 : texte = "O : Tierras de Fuego"; break;
        case 522 : texte = "E : Pueblo de la Sombra*- Prohibido a los seres vivos -"; break;
        case 523 : texte = "Templo de las tinieblas**Si eres un fantasma y que buscas un trabajo, más bien vente a estar parado aquí."; break;
        case 524 : texte = "N : Pueblo de la Sombra*O : Lago de Hylia"; break;
        case 525 : texte = "N : Cementerio de los Espíritus**Entrada prohibida"; break;
        case 526 : texte = "Pueblo de la Sombra"; break;
        case 527 : texte = "Vendo una botella por 100 rupias, quieres ?*              SI ?            no  "; break;
        case 528 : texte = "Vendo una botella por 100 rupias, quieres ?*              si              NO ?"; break;
        case 529 : texte = "Lo siento, pero no tienes bastantes rupias."; break;
        case 530 : texte = "Muchas gracias, he aquí tu botella."; break;
        case 531 : texte = "Vuelve si cambias de opinión."; break;
        case 532 : texte = "Lo siento, no tengo más botellas."; break;
        case 533 : texte = "Has encontrado una botella vacía !!!**Podrás utilizarla para almacenar pozimas !!!"; break;
        case 535 : texte = "Los habitantes de este pueblo tienen un dialecto muy especial, no entiendo nada..."; break;
        case 536 : texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 537 : texte = "Obten una autorization del jefe si quieres pasar de verdad !!!"; break;
        case 538 : texte = "El jefe te autorizó ??? Grrrr... Pues apartate!!!"; break;
        case 539 : texte = "Fuera de aquí !!!"; break;
        case 540 : texte = "No solemos ver muchos visitantes por aquí..."; break;
        case 541 : texte = "Los monstruos de aquí no temen muchas cosas, por suerte atacan solo los humanos."; break;
        case 542 : texte = "De verdad ?*Entiendes lo que digo ?"; break;
        case 543 : texte = "N : Desierto y Pueblo Gerudo"; break;
        case 544 : texte = "S : Lago de Hylia*O : Castillo de Hyrule"; break;
        case 545 : texte = "Pueblo Kakariko"; break;
        case 546 : texte = "O : Castillo de Hyrule"; break;
        case 547 : texte = "Que día tan bueno !!!"; break;
        case 548 : texte = "Pero porque acepté cuidar estos bichos ???*Odio las gallinas !!!"; break;
        case 549 : texte = "Se encuentran muchas cosas en las tiendas de este pueblo."; break;
        case 550 : texte = "S : Pueblo Kakariko*O : Desierto*E : Montaña de la Muerte"; break;
        case 551 : texte = "Pueblo Gerudo"; break;
        case 552 : texte = "Perdido en el desierto ?*Estas aquí :*                        X"; break;
        case 554 : texte = "S : Hacia el Castillo de Hyrule"; break;
        case 555 : texte = "Templo del Desierto**Ven a probar nuestros baños.*(agua no potable)"; break;
        case 556 : texte = "Templo del Bosque**Salve los árboles, coma castor!!!"; break;
        case 557 : texte = "Templo del Lago**Gorro de baño obligatorio."; break;
        case 558 : texte = "Templo de Hielo**El personal insiste en recordar que un calabozo no es una pista de patinaje."; break;
        case 559 : texte = "Has visto el herrero del pueblo ?*Dicen que es muy avispado para mejorar el equipo de los aventureros, mucha gente le visita."; break;
        case 560 : texte = "El templo esta en el fondo del desierto, en puesto de una antigua oasis."; break;
        case 561 : texte = "S : Tierras de Fuego*E : Pueblo Kakariko"; break;
        case 562 : texte = "Castillo de Hyrule"; break;
        case 563 : texte = "E : Pueblo Kakariko"; break;
        case 564 : texte = "O : Tortuga de Roca*E : Lago de Hylia"; break;
        case 565 : texte = "Templo Oculto**Aquí descansa la Espada del Golpe Contra el Mal, la Espada Maestra."; break;
        case 566 : texte = "N : Hacia el Cimenterio encantado"; break;
#ifdef __vita__
        case 567 : texte = "Has encontrado el mapa del calabozo !!!*Pulsa ¾7 para verlo."; break;
#else
        case 567 : texte = "Has encontrado el mapa del calabozo !!!*Pulsa P para verlo."; break;
#endif
        case 568 : texte = "Has encontrado la brújula !!!*Puedes localizar el jefe y las arcas sobre el mapa."; break;
        case 569 : texte = "Has encontrado la llave del jefe !!!"; break;
        case 570 : texte = "Has encontrado una llave pequeña !!!*Acercate de una puerta para abrirla."; break;
#ifdef __vita__
        case 571 : texte = "Has encontrado los Guantes !!!*Utilizalos para levantar objetos equipandolos o pulsando ¾3."; break;
#else        
        case 571 : texte = "Has encontrado los Guantes !!!*Utilizalos para levantar objetos equipandolos o pulsando C."; break;
#endif        
        case 572 : texte = "Has encontrado un cristal magico !!!"; break;
        case 573 : texte = "Cómo podría ser útil... ?"; break;
        case 574 : texte = "Te quedan aún "+s+" por encontrar !!!"; break;
        case 575 : texte = "Solo 2 que encontrar !!!"; break;
        case 576 : texte = "Te falta solo uno !!!"; break;
        case 577 : texte = "Tienes todo los cristales, corre hasta el castillo a salvar a Zelda !!!"; break;
        case 580 : texte = "Has encontrado el lanzagarfios !!! *Utilizalo para atravesar obstáculos."; break;
        case 581 : texte = "Has encontrado la lampara !!! *Utilizala para hacer surgir llamas."; break;
        case 582 : texte = "Has encontrado las aletas !!! *Equipalas para ir en el agua."; break;
        case 583 : texte = "Has encontrado el martillo mágico !!! *Utilizalo para hundir obstáculos."; break;
        case 584 : texte = "Has encontrado la varilla de fuego !!! *De ahora en adelante puedes lanzar potentes llamas remotas"; break;
        case 585 : texte = "Has encontrado la varilla de hielo !!! *Utilizala para congelar todo a distancia."; break;
        case 586 : texte = "Has encontrado la Espada Maestra !!! *Incluso Ganon no debería ser capaz de resistir a su potencia !!! (en teoría)"; break;
        case 587 : texte = "Felicitaciones Link, has conseguido venir a liberarme!!!***Vamonos de prisa a encontrar a Ganon, tenemos que retomar la Trifuerza a toda costa !"; break;
        case 589 : texte = "El paso secreto detrás de la sala del trono lleva a Ganon. Vamos rapido !"; break;
        case 590 : texte = "Casi hemos llegado, sigueme !"; break;
        case 591 : texte = "Tengo miedo que no puedas nunca vencer a Ganon con tus armas actuales...*Ve a hablar con el jefe del pueblo Kakariko, estoy segura que él va a encontrar una solución."; break;
        case 592 : texte = "Ganon esta ya detrás de esta puerta, voy a curarte las heridas."; break;
        case 593 : texte = "Ganon todavía esta en algún sitio del castillo."; break;
        case 594 : texte = "Tendrías que esperar a la princesa Zelda !!!"; break;
        case 595 : texte = "No tienes la extraña impresión de olvidar a alguien por casualidad ???"; break;
        case 596 : texte = "Zelda te esta esperando!!!"; break;
        case 597 : texte = "Has encontrado la Trifuerza!!!"; break;
        case 598 : texte = "Has encontrado el libro de Mudora!!! **Ahora entiendes el hyliano antiguo!!!"; break;
        case 599 : texte = "Felicitaciones Link, has conseguido encontrarme. En recompensa, te ofrezco el pendiente de Din, aumenta tu defensa de un punto."; break;
        case 600 : texte = "Felicitaciones Link, has conseguido encontrarme. En recompensa, te ofrezco el pendiente de Nayru, aumenta tu defensa de dos puntos!!!"; break;
        case 601 : texte = "..."; break;
        case 602 : texte = "Has obtenido un pendiente mágico !!!**Tu defensa acaba de aumentar!!!"; break;
        case 603 : texte = "Felicitaciones Link, has conseguido encontrarme. Para recompensarte, voy a doblar la capacidad de tu reserva de magia!!!"; break;
        case 604 : texte = "Tu reserva de magia ha doblado!!!"; break;
        case 605 : texte = "Vuelve cuando tengas una botella vacía  y te venderé una pozima roja que te devuelve la energia."; break;
        case 606 : texte = "Una pozima roja por 60 rupias, la quieres ?*              SI ?            no  "; break;
        case 607 : texte = "Una pozima roja para 60 rupias, la quieres ?*              si              NO ?"; break;
        case 608 : texte = "Gracias, toma tu pozima.";break;
        case 609 : texte = "Has obtenido una pozima roja !!!*Bebela para renovar tu energia!!!"; break;
        case 610 : texte = "Has obtenido una pozima verde !!!*Bebela para renovar tu magia!!!"; break;
        case 611 : texte = "Has obtenido una pozima azul !!!*Bebela para renovar tu energia y tu magia!!!"; break;
        case 612 : texte = "Ola, en que puedo ayudarle ?"; break;
        case 613 : texte = "Hic! Dicen que una hada daría objetos encantados... Hic! ...a los aventureros que la encuentran... Hic!!!"; break;
        case 614 : texte = "Un corazón por 10 rupias, vale ?**              SI ?            no  "; break;
        case 615 : texte = "Un corazón por 10 rupias, vale ?**             si              NO ?"; break;
        case 616 : texte = "Un poco de magia por 20 rupias, vale ?**              SI ?            no  "; break;
        case 617 : texte = "Un poco de magia por 20 rupias, vale ?**              si              NO ?"; break;
        case 618 : texte = "Mucho magia por 30 rupias, vale ?**              SI ?            no  "; break;
        case 619 : texte = "Mucho magia por 30 rupias, vale ?**              si              NO ?"; break;
        case 620 : texte = "5 flechas por 30 rupias, vale ?**              SI ?            no  "; break;
        case 621 : texte = "5 flechas por 30 rupias, vale ?**              si              NO ?"; break;
        case 622 : texte = "Una bomba por 30 rupias, vale ?**              SI ?            no  "; break;
        case 623 : texte = "Una bomba por 30 rupias, vale ?**              si              NO ?"; break;
        case 624 : texte = "Un arco por 1000 rupias, vale ?**              SI ?            no  "; break;
        case 625 : texte = "Un arco por 1000 rupias, vale ?**              si              NO ?"; break;
        case 626 : texte = "Un arco por 50 rupias, vale ?**              SI ?            no  "; break;
        case 627 : texte = "Un arco por 50 rupias, vale ?**              si              NO ?"; break;
        case 628 : texte = "No necesitas eso ahora."; break;
        case 629 : texte = "Gracias."; break;
        case 630 : texte = "Has obtenido el arco !!!*Utilizalo para alcanzar objetivos alejados."; break;
        case 631 : texte = "Elige lo que quieras."; break;
        case 632 : texte = "Que ???*Estas en contratado por el jefe ???*Pues vale, te hago une reducción sobre el arco..."; break;
        case 633 : texte = "Buenos días Link, soy el jefe de este pueblo, me figuraba que vendriás."; break;
        case 634 : texte = "Desde esta mañana monstruos aparecen en muchas partes de Hyrule, he intentado ir a hablar de eso con la princesa Zelda, pero como quizás ya lo has notado, un poderoso hechizo bloquea el acceso al castillo..."; break;
        case 636 : texte = "Dices que Ganon es responsable de todo esto ? Que ha robado la Trifuerza y que encarcela la princesa Zelda en el castillo ?"; break;
        case 637 : texte = "Pues... la situación es mucho más grave que lo que creía..."; break;
        case 638 : texte = "Tenemos que obrar rapidamente, debes enfrentar a Ganon de nuevo!"; break;
        case 639 : texte = "Cómo entrar en el castillo ? Quizás tenga una idea..."; break;
        case 640 : texte = "Como lo sabes, el poder de los 7 Hombres Sabios fue encerrado en 7 cristales por el mago Aghanim mientras intentaba quitar el hechizo que confinaba Ganon en el Dark World."; break;
        case 641 : texte = "Ahora bien, aunque resucitaste las descendientes de los hombres sabios despues de vencer a Ganon y de encontrar la Trifuerza, estos cristales conservaron sus potencia."; break;
        case 642 : texte = "Estan escondidos en los 7 templos, reúnelos todos y podrás ir más allá del sortilego de Ganon."; break;
        case 643 : texte = "Sin embargo, será una tarea muy dura, Ganon sin duda ha debido de enviar sus mejores unidades a proteger esos cristales..."; break;
        case 644 : texte = "Una ultima cosa, no irás muy lejos con tu equipo actual. Ve a ver al vendedor de armas y dile que vienes de mi parte. Seguro que tu ayudará."; break;
        case 645 : texte = "Ve a ver el vendedor de armas y dile que vienes de mi parte. Seguro que tu ayudará."; break;
        case 646 : texte = "Tienes que reunir los 7 cristales si quieres tener una posibilidad de salvar a Zelda y Hyrule..."; break;
        case 647 : texte = "Has encontrado los 7 cristales ?  Ve al castillo, primero debes liberar a la princesa, ella sabrá mejor que yo cómo salvar Hyrule."; break;
        case 648 : texte = "Tus armas no tienen efecto sobre Ganon ? En este caso tienes que encontrar la Espada Maestra. Se dice que fue disimulada en un templo secreto.*Se dice tambien que el camino que conduce a la Espada del Golpe Contra el Mal pasa por un pueblo lleno de monstros...*Me pregunto si tal pueblo existe..."; break;
        case 650 : texte = "No obstante tengo miedo que tu equipo actual sea insuficiente para acceder a este templo, a lo mejor deberías ir a ver al herrero del pueblo Gerudo..."; break;
        case 651 : texte = "Ya es hora de enfrentarse a Ganon y de recuperar la Trifuerza!"; break;
        case 652 : texte = "Hey! Hay que pagar para abrir una de mis arcas!!!"; break;
        case 653 : texte = "Una de estas arcas contiene un cuarto de corazón, quieres probar tu fortuna por 10 rupias ? Podrás abrir solo una, vale ?*              SI ?            no  "; break;
        case 654 : texte = "Una de estas arcas contiene un cuarto de corazón, quieres probar tu fortuna por 10 rupias ? Podrás abrir solo una, vale ?*              si              NO ?"; break;
        case 655 : texte = "Elige un arca."; break;
        case 656 : texte = "No tengo más premios que poner en juego, lo siento."; break;
        case 657 : texte = "Has perdido! Este arca esta vacía."; break;
        case 658 : texte = "Buenos días! Si estas aquí para ver el herrero, vive un poco más lejos."; break;
        case 659 : texte = "Ola Link, soy el jefe de este pueblo.*Deberías ir a ver el herrero y monstrarle lo que quieres que mejore en tu equipo."; break;
        case 660 : texte = "He sido informado de tu búsqueda, entonces me puse de acuerdo con el.*Todo será gratis para ti."; break;
        case 661 : texte = "No necesitas beber esta pozima ahora."; break;
        case 662 : texte = "Una pozima verde por 40 rupias, la quieres ?*              SI ?            no  "; break;
        case 663 : texte = "Una pozima verde por 40 rupias, la quieres ?*              si              NO ?"; break;
        case 664 : texte = "Vuelve cuando tengas una botella vacía y te venderé una pozima verde que rellena la magia."; break;
        case 665 : texte = "Vuelve más tarde, estoy agobiado!"; break;
        case 666 : texte = "Puedo hacer algo para ti ?"; break;
        case 667 : texte = "Quieres que mejore tu espada ?**              SI ?            no  "; break;
        case 668 : texte = "Quieres que mejore tu espada ?**              si              NO ?"; break;
        case 669 : texte = "Tu espada ha triplicado de potencia y puede ahora devolver algunos ataques magicos, guay!!!"; break;
        case 670 : texte = "Quieres que mejore tus guantes ?**              SI ?            no  "; break;
        case 671 : texte = "Quieres que mejore tus guantes ?**              si              NO ?"; break;
        case 672 : texte = "La potencia de tus guantes te permite ahora levantar rocas pesadas."; break;
        case 673 : texte = "Quieres que mejore tu arco ?**              SI ?            no  "; break;
        case 674 : texte = "Quieres que mejore tu arco ?**              si              NO ?"; break;
        case 675 : texte = "Tu arco tira ahora flechas de plata de una potencia devastadora !!!"; break;
        case 676 : texte = "Vuelve cuando tengas una botella vacía y te venderé una pozima azul que rellena la energia y la magia."; break;
        case 677 : texte = "Una pozima azul por 160 rupias, la quieres ?*              SI ?            no  "; break;
        case 678 : texte = "Una pozima azul por 160 rupias, la quieres ?*              si              NO ?"; break;
        case 679 : texte = "Nuestro pueblo fue fundado para impedir a los aventureros imprudentes que tengan acceso al templo, no da el permiso para pasar a cualquiera."; break;
        case 680 : texte = "Mmmm... Ya has encontrado 4 cristales ?*Tengo que confesar que me impresionas..."; break;
        case 681 : texte = "Pues entendido, tienes el permiso para pasar por el cementerio, por tu cuenta y riesgo."; break;
        case 682 : texte = "Ve a hablar al guardia al norte del pueblo, te dejará pasar."; break;
        case 683 : texte = "Veo que siempre estas vivo...*Sorprendente."; break;
        case 684 : texte = "El templo de las tinieblas es el punto de partida del camino que conduce a un objeto de leyenda. Este pueblo solo sirve para disuadir a los aventureros de acercarse demasiado."; break;
        case 685 : texte = "Has encontrado la Espada ?*Pero no creas que es tuya por eso."; break;
        case 686 : texte = "La Espada Maestra forma parte del patrimonio el más valioso de Hyrule con la Trifuerza, tendrás que devolverla en su santuario en cuanto acabes tu misión."; break;
        case 687 : texte = "Los habitantes de este pueblo son todos espíritus que han contestado a la llamada de la princesa Zelda."; break;
        case 688 : texte = "Cuando devolviste la paz sobre Hyrule y reunificaste el Light World con el Golden Land, Zelda preguntó en secreto a los espíritus voluntarios que crean este pueblo para bloquear"; break;
        case 689 : texte = "el acceso a un objeto muy valioso."; break;        
        case 690 : texte = "Bienvenido Link!*Dejame explicarte lo que hago aquí."; break;
        case 691 : texte = "Como ya lo has notado sin duda, monstruos han aparecido por todas partes en Hyrule. Es la primera vez que veo monstruos despues que venciste a Ganon."; break;
        case 692 : texte = "Pues he decidido catalogarlos todos."; break;
        case 693 : texte = "El problema es que soy demasiado miedoso para ir al encuentro de ellos, necesito tu ayuda."; break;
        case 694 : texte = "Tienes que golpear cada tipo de monstruo y venir a hacerme tu informe."; break;
        case 695 : texte = "Te recompensaré cada vez que mates 7 nuevos tipos de enemigo."; break;
#ifdef __vita__
        case 696 : texte = "Si quieres ver que enemigos ya has vencido, pulsa ¾6"; break;
#else
        case 696 : texte = "Si quieres ver que enemigos ya has vencido, pulsa M."; break;
#endif
        case 697 : texte = "Con "+s+" mas enemigos diferentes tendras la proxima recompensa."; break;
        case 698 : texte = "Te falta solo uno nuevo enemigo antes de la proxima recompensa!!!"; break;
        case 699 : texte = "Acepta este regalo por tu contribución en mi proyecto :"; break;
        case 700 : texte = "Lo siento pero no tengo nada más que regalarte..."; break;
        case 701 : texte = "No me le puedo creer, has conseguido vencer cada tipo de enemigo !!!*Felicitaciones Link !!!"; break;        
        case 702 : texte = "                    Nivel 1 :**               Templo del Bosque"; break;
        case 703 : texte = "                    Nivel 2 :**                Templo del Agua"; break;
        case 704 : texte = "                    Nivel 3 :**              Templo de la Montaña"; break;
        case 705 : texte = "                    Nivel 4 :**              Templo del Desierto"; break;
        case 706 : texte = "                    Nivel 5 :**            Templo de las Tinieblas"; break;
        case 707 : texte = "                    Nivel 6 :**                Templo del Fuego"; break;
        case 708 : texte = "                    Nivel 7 :**                Templo de Hielo"; break;
        case 709 : texte = "                    Nivel ? :**                 Templo Oscuro"; break;
        case 710 : texte = "                  Nivel Final :**               Castillo de Hyrule"; break;        
        case 711 :texte = "               Ya estas cansado ?               ?                   SEGUIR                  ?                  Grabar y dejar                                Dejar sin grabar              "; break;
        case 712 :texte = "               Ya estas cansado ?                                   Seguir                     ?               GRABAR Y DEJAR              ?                 Dejar sin grabar              "; break;
        case 713 :texte = "               Ya estas cansado ?                                   Seguir                                     Grabar y dejar                 ?              DEJAR SIN GRABAR             ?"; break;
        case 714 : texte = "En el momento en que Link tocó la Trifuerza, los monstruos desaparecieron y la paz volvió.**La princesa Zelda tomó entonces una gran decisión: tocó a su vez la Trifuerza para formular su deseo...**La Trifuerza siempre fue el origen de los problemas sobrevenidos en el Reino,  tarde o temprano una otra criatura dañina habría acabado encontrandola.**Al mismo tiempo que la princesa tocó la reliquia, desapareció para siempre de Hyrule.";
        case 715 : texte = "Desde ese día, el pueblo de Hyrule vivió en paz, sin temer nuevos desastres.**Asi se acaba la leyenda de Zelda, de la  Trifuerza y del Golden Land.**Se dice que la Espada Maestra descansa en seguridad en cualquier lugar, y que es el ultimo recuerdo de la búsqueda de Link..."; break;
        case 716 : texte = "Felicitaciones Link, has conseguido encontrarme. En recompensa, te ofrezco el pendiente de Farore, aumenta tu defensa de un punto."; break;
        case 717 : texte = "Quieres grabar tu juego ?**                      ? SI ?*                        no  "; break;
        case 718 : texte = "Quieres grabar tu juego ?**                        si  *                      ? NO ?"; break;
        case 719 : texte = "Juego grabado."; break;
        case 720 : texte = "El Reino de Hyrule estaba en paz desde que Link, ultimo cavallero hyliano, había vencido el maléfico Ganon y había recuperado la valiosa Trifuerza."; break;
        case 721 : texte = "Nadie sabe que deseo hizo Link tocando la Trifuerza, pero tuvo como efecto de reunificar el Light World y el Dark World, y volvió a los descendientes de los 7 Hombres Sabios a la vida."; break;
        case 722 : texte = "Despues Link devolvió a la princesa Zelda la Trifuerza y la Espada Maestra, y el pueblo se puso a creer que la paz duraria.*Pero el pueblo se equivocaba..."; break;
        case 723 : texte = "El deseo de Link a la Trifuerza igualmente tuvo lamentables efectos. Ganon y sus esbirros fuen asi resucitados y se dispusieron a atacar."; break;
        case 724 : texte = "En alguna parte del bosque de Hyrule, Link duerme sin sospechar que Ganon ya ha pasado al ataque,"; break;
        case 725 : texte ="hasta que una voz familiar le habla en su sueño..."; break;
        case 726 : texte = "Ayuda!*Ayuda!*Soy yo! Zelda!*Te hablo por telepatía."; break;
        case 727 : texte = "Estoy prisionera en el torreón del castillo! Necesito tu ayuda!*Ganon esta de vuelta, y sin duda ya ha encontrado la Trifuerza a estas horas..."; break;
        case 728 : texte = "Corre al castillo Link, eres mi única esperanza..."; break;
#ifdef __vita__
        case 729 : texte = "AYUDA : Pulsa Select para consultar la ayuda."; break;
#else
        case 729 : texte = "AYUDA : Pulsa F1 para consultar la ayuda."; break;
#endif
        default : 
            texte = "ERROR TEXTO";
    }

    return texte;
}

void Texte::chercheText() {
    ostringstream os;
    int tmp;
    switch (id) {
        case 1  : texte = (this->*getTextByLangFunc)(501, os.str()); break;
        case 2  : texte = (this->*getTextByLangFunc)(502, os.str()); break;
        case 3  : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = (this->*getTextByLangFunc)(503, os.str());
            if (tmp<4) buffer = (this->*getTextByLangFunc)(504, os.str());
            else buffer = (this->*getTextByLangFunc)(505, os.str());
            break;
        case 11 : texte = (this->*getTextByLangFunc)(511, os.str()); break;
        case 12 : texte = (this->*getTextByLangFunc)(512, os.str()); break;
        case 13 : texte = (this->*getTextByLangFunc)(513, os.str()); break;
        case 14 : texte = (this->*getTextByLangFunc)(514, os.str()); break;
        case 15 : texte = (this->*getTextByLangFunc)(515, os.str()); break;
        case 16 : texte = (this->*getTextByLangFunc)(516, os.str()); break;
        case 17 : texte = (this->*getTextByLangFunc)(517, os.str()); break;
        case 18 : texte = (this->*getTextByLangFunc)(518, os.str()); break;
        case 19 : texte = (this->*getTextByLangFunc)(519, os.str()); break;
        case 20 : texte = (this->*getTextByLangFunc)(520, os.str()); break;
        case 21 : texte = (this->*getTextByLangFunc)(521, os.str()); break;
        case 22 : texte = (this->*getTextByLangFunc)(522, os.str()); break;
        case 23 : texte = (this->*getTextByLangFunc)(523, os.str()); break;
        case 24 : texte = (this->*getTextByLangFunc)(524, os.str()); break;
        case 25 : texte = (this->*getTextByLangFunc)(525, os.str()); break;
        case 26 : texte = (this->*getTextByLangFunc)(526, os.str()); break;
        case 27 : texte = (this->*getTextByLangFunc)(527, os.str()); 
            if ((gpJeu->getJoueur()->hasBouteille(0) && gpJeu->getZone()==8)
            || (gpJeu->getJoueur()->hasBouteille(1) && gpJeu->getZone()==5)
            || (gpJeu->getJoueur()->hasBouteille(2) && gpJeu->getZone()==6)) {id=32; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) idsuiv=29;
            else idsuiv=30;
            break;
        case 28 : texte = (this->*getTextByLangFunc)(528, os.str()); idsuiv=31; break;
        case 29 : texte = (this->*getTextByLangFunc)(529, os.str()); break;
        case 30 : texte = (this->*getTextByLangFunc)(530, os.str()); break;
        case 31 : texte = (this->*getTextByLangFunc)(531, os.str()); break;
        case 32 : texte = (this->*getTextByLangFunc)(532, os.str()); break;
        case 33 : texte = (this->*getTextByLangFunc)(533, os.str()); break;
        case 35 : texte = (this->*getTextByLangFunc)(535, os.str()); break;
        case 36 : texte = (this->*getTextByLangFunc)(536, os.str()); break;
        case 37 : texte = (this->*getTextByLangFunc)(537, os.str()); break;
        case 38 : texte = (this->*getTextByLangFunc)(538, os.str()); break;
        case 39 : texte = (this->*getTextByLangFunc)(539, os.str()); break;
        case 40 : texte = (this->*getTextByLangFunc)(540, os.str()); break;
        case 41 : texte = (this->*getTextByLangFunc)(541, os.str()); break;
        case 42 : texte = (this->*getTextByLangFunc)(542, os.str()); break;
        case 43 : texte = (this->*getTextByLangFunc)(543, os.str()); break;
        case 44 : texte = (this->*getTextByLangFunc)(544, os.str()); break;
        case 45 : texte = (this->*getTextByLangFunc)(545, os.str()); break;
        case 46 : texte = (this->*getTextByLangFunc)(546, os.str()); break;
        case 47 : texte = (this->*getTextByLangFunc)(547, os.str()); break;
        case 48 : texte = (this->*getTextByLangFunc)(548, os.str()); break;
        case 49 : texte = (this->*getTextByLangFunc)(549, os.str()); break;
        case 50 : texte = (this->*getTextByLangFunc)(550, os.str()); break;
        case 51 : texte = (this->*getTextByLangFunc)(551, os.str()); break;
        case 52 : texte = (this->*getTextByLangFunc)(552, os.str()); break;
        case 54 : texte = (this->*getTextByLangFunc)(554, os.str()); break;
        case 55 : texte = (this->*getTextByLangFunc)(555, os.str()); break;
        case 56 : texte = (this->*getTextByLangFunc)(556, os.str()); break;
        case 57 : texte = (this->*getTextByLangFunc)(557, os.str()); break;
        case 58 : texte = (this->*getTextByLangFunc)(558, os.str()); break;
        case 59 : texte = (this->*getTextByLangFunc)(559, os.str()); break;
        case 60 : texte = (this->*getTextByLangFunc)(560, os.str()); break;
        case 61 : texte = (this->*getTextByLangFunc)(561, os.str()); break;
        case 62 : texte = (this->*getTextByLangFunc)(562, os.str()); break;
        case 63 : texte = (this->*getTextByLangFunc)(563, os.str()); break;
        case 64 : texte = (this->*getTextByLangFunc)(564, os.str()); break;
        case 65 : texte = (this->*getTextByLangFunc)(565, os.str()); break;
        case 66 : texte = (this->*getTextByLangFunc)(566, os.str()); break;
        case 67 : texte = (this->*getTextByLangFunc)(567, os.str()); break;
        case 68 : texte = (this->*getTextByLangFunc)(568, os.str()); break;
        case 69 : texte = (this->*getTextByLangFunc)(569, os.str()); break;
        case 70 : texte = (this->*getTextByLangFunc)(570, os.str()); break;
        case 71 : texte = (this->*getTextByLangFunc)(571, os.str()); break;
        case 72 : 
            texte = (this->*getTextByLangFunc)(572, os.str());; 
            tmp = 7-gpJeu->getJoueur()->nbCristaux();
            os << tmp;
            if (tmp==6 && !gpJeu->getJoueur()->getAvancement()) buffer = (this->*getTextByLangFunc)(573, os.str());
            else if (tmp>2) buffer = (this->*getTextByLangFunc)(574, os.str());
            else if (tmp==2) buffer = (this->*getTextByLangFunc)(575, os.str());
            else if (tmp==1) buffer = (this->*getTextByLangFunc)(576, os.str());
            else if (tmp==0) buffer = (this->*getTextByLangFunc)(577, os.str());
            break;
        case 80 : texte = (this->*getTextByLangFunc)(580, os.str());; break;
        case 81 : texte = (this->*getTextByLangFunc)(581, os.str()); break;
        case 82 : texte = (this->*getTextByLangFunc)(582, os.str()); break;
        case 83 : texte = (this->*getTextByLangFunc)(583, os.str()); break;
        case 84 : texte = (this->*getTextByLangFunc)(584, os.str()); break;
        case 85 : texte = (this->*getTextByLangFunc)(585, os.str()); break;
        case 86 : texte = (this->*getTextByLangFunc)(586, os.str()); break;
        case 87 : texte = (this->*getTextByLangFunc)(587, os.str()); break;
        case 89 : texte = (this->*getTextByLangFunc)(589, os.str()); break;
        case 90 : texte = (this->*getTextByLangFunc)(590, os.str()); break;
        case 91 : texte = (this->*getTextByLangFunc)(591, os.str()); break;
        case 92 : texte = (this->*getTextByLangFunc)(592, os.str()); break;
        case 93 : texte = (this->*getTextByLangFunc)(593, os.str()); break;
        case 94 : texte = (this->*getTextByLangFunc)(594, os.str()); break;
        case 95 : texte = (this->*getTextByLangFunc)(595, os.str()); break;
        case 96 : texte = (this->*getTextByLangFunc)(596, os.str()); break;
        case 97 : texte = (this->*getTextByLangFunc)(597, os.str()); break;
        case 98 : texte = (this->*getTextByLangFunc)(598, os.str()); break;
        case 99 : texte = (this->*getTextByLangFunc)(599, os.str()); break;
        case 100 : texte = (this->*getTextByLangFunc)(600, os.str()); break;
        case 101 : texte = (this->*getTextByLangFunc)(601, os.str());; break;
        case 102 : texte = (this->*getTextByLangFunc)(602, os.str()); break;
        case 103 : texte = (this->*getTextByLangFunc)(603, os.str()); break;
        case 104 : texte = (this->*getTextByLangFunc)(604, os.str()); break;
        case 105 : texte = (this->*getTextByLangFunc)(605, os.str()); break;
        case 106 : texte = (this->*getTextByLangFunc)(606, os.str());
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=105; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=29;
            else idsuiv=108; break;
        case 107 : texte = (this->*getTextByLangFunc)(607, os.str()); break;
        case 108 : texte = (this->*getTextByLangFunc)(608, os.str());break;
        case 109 : texte = (this->*getTextByLangFunc)(609, os.str()); break;
        case 110 : texte = (this->*getTextByLangFunc)(610, os.str()); break;
        case 111 : texte = (this->*getTextByLangFunc)(611, os.str()); break;
        case 112 : texte = (this->*getTextByLangFunc)(612, os.str()); break;
        case 113 : texte = (this->*getTextByLangFunc)(613, os.str()); break;
        case 114 : texte = (this->*getTextByLangFunc)(614, os.str()); 
            if (gpJeu->getJoueur()->getVie()+gpJeu->getJoueur()->getBoostVie()
            == gpJeu->getJoueur()->getVieMax()) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=29;
            else idsuiv=129; break;
        case 115 : texte = (this->*getTextByLangFunc)(615, os.str()); break;
        case 116 : texte = (this->*getTextByLangFunc)(616, os.str());
            if (gpJeu->getJoueur()->getMagie()+gpJeu->getJoueur()->getBoostMagie()
            == gpJeu->getJoueur()->getMagieMax() || !gpJeu->getJoueur()->hasObjet(O_LANTERNE)) {
                id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=29;
            else idsuiv=129; break;
        case 117 : texte = (this->*getTextByLangFunc)(617, os.str()); break;
        case 118 : texte = (this->*getTextByLangFunc)(618, os.str());
            if (gpJeu->getJoueur()->getMagie()+gpJeu->getJoueur()->getBoostMagie()
            == gpJeu->getJoueur()->getMagieMax() || !gpJeu->getJoueur()->hasObjet(O_LANTERNE)) {
                id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 119 : texte = (this->*getTextByLangFunc)(619, os.str()); break;
        case 120 : texte = (this->*getTextByLangFunc)(620, os.str());
            if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax() 
            || !gpJeu->getJoueur()->hasObjet(O_ARC)) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 121 : texte = (this->*getTextByLangFunc)(621, os.str()); break;
        case 122 : texte = (this->*getTextByLangFunc)(622, os.str()); 
            if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax() 
            || !gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 123 : texte = (this->*getTextByLangFunc)(623, os.str()); break;
        case 124 : texte = (this->*getTextByLangFunc)(624, os.str()); 
            idsuiv=29; break;
        case 125 : texte = (this->*getTextByLangFunc)(625, os.str()); break;
        case 126 : texte = (this->*getTextByLangFunc)(626, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<50) idsuiv=29;
            else idsuiv=129; break;
        case 127 : texte = (this->*getTextByLangFunc)(627, os.str()); break;
        case 128 : texte = (this->*getTextByLangFunc)(628, os.str()); break;
        case 129 : texte = (this->*getTextByLangFunc)(629, os.str()); break;
        case 130 : texte = (this->*getTextByLangFunc)(630, os.str()); break;
        case 131 : texte = (this->*getTextByLangFunc)(631, os.str()); break;
        case 132 : texte = (this->*getTextByLangFunc)(632, os.str()); break;
        case 133 : texte = (this->*getTextByLangFunc)(633, os.str()); idsuiv=134; break;
        case 134 : texte = (this->*getTextByLangFunc)(634, os.str()); idsuiv=136; break;
        case 136 : texte = (this->*getTextByLangFunc)(636, os.str()); idsuiv=137; break;
        case 137 : texte = (this->*getTextByLangFunc)(637, os.str()); idsuiv=138; break;
        case 138 : texte = (this->*getTextByLangFunc)(638, os.str()); idsuiv=139; break;
        case 139 : texte = (this->*getTextByLangFunc)(639, os.str()); idsuiv=140; break;
        case 140 : texte = (this->*getTextByLangFunc)(640, os.str()); idsuiv=141; break;
        case 141 : texte = (this->*getTextByLangFunc)(641, os.str()); idsuiv=142; break;
        case 142 : texte = (this->*getTextByLangFunc)(642, os.str()); idsuiv=143; break;
        case 143 : texte = (this->*getTextByLangFunc)(643, os.str()); idsuiv=144; break;
        case 144 : texte = (this->*getTextByLangFunc)(644, os.str());; break;
        case 145 : texte = (this->*getTextByLangFunc)(645, os.str()); break;
        case 146 : texte = (this->*getTextByLangFunc)(646, os.str()); break;
        case 147 : texte = (this->*getTextByLangFunc)(647, os.str()); break;
        case 148 : texte = (this->*getTextByLangFunc)(648, os.str()); break;
        case 150 : texte = (this->*getTextByLangFunc)(650, os.str()); break;
        case 151 : texte = (this->*getTextByLangFunc)(651, os.str()); break;
        case 152 : texte = (this->*getTextByLangFunc)(652, os.str()); break;
        case 153 : texte = (this->*getTextByLangFunc)(653, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=29; break;
        case 154 : texte = (this->*getTextByLangFunc)(654, os.str()); break;
        case 155 : texte = (this->*getTextByLangFunc)(655, os.str()); break;
        case 156 : texte = (this->*getTextByLangFunc)(656, os.str()); break;
        case 157 : texte = (this->*getTextByLangFunc)(657, os.str()); break;
        case 158 : texte = (this->*getTextByLangFunc)(658, os.str()); break;
        case 159 : texte = (this->*getTextByLangFunc)(659, os.str());
            buffer = (this->*getTextByLangFunc)(660, os.str()); break;
        case 160 : texte = (this->*getTextByLangFunc)(661, os.str()); break;
        case 161 : texte = (this->*getTextByLangFunc)(662, os.str());
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=163; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=29;
            else idsuiv=108; break;
        case 162 : texte = (this->*getTextByLangFunc)(663, os.str()); break;
        case 163 : texte = (this->*getTextByLangFunc)(664, os.str()); break;
        case 164 : texte = (this->*getTextByLangFunc)(665, os.str()); break;
        case 165 : texte = (this->*getTextByLangFunc)(666, os.str());
            if (gpJeu->getJoueur()->getEpee()==1) {id=166; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_GANTS)==1 && gpJeu->getJoueur()->getObjet()==8) {
                id=169; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_ARC)==2 && gpJeu->getJoueur()->getObjet()==0 
            && gpJeu->getJoueur()->nbCristaux()==7) {
                id=172; chercheText();break;}
            break;
        case 166 : texte = (this->*getTextByLangFunc)(667, os.str()); break;
        case 167 : texte = (this->*getTextByLangFunc)(668, os.str()); break;
        case 168 : texte = (this->*getTextByLangFunc)(669, os.str()); break;
        case 169 : texte = (this->*getTextByLangFunc)(670, os.str()); break;
        case 170 : texte = (this->*getTextByLangFunc)(671, os.str()); break;
        case 171 : texte = (this->*getTextByLangFunc)(672, os.str()); break;
        case 172 : texte = (this->*getTextByLangFunc)(673, os.str()); break;
        case 173 : texte = (this->*getTextByLangFunc)(674, os.str()); break;
        case 174 : texte = (this->*getTextByLangFunc)(675, os.str()); break;
        case 175 : texte = (this->*getTextByLangFunc)(676, os.str()); break;
        case 176 : texte = (this->*getTextByLangFunc)(677, os.str());
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=175; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=29;
            else idsuiv=108; break;
        case 177 : texte = (this->*getTextByLangFunc)(678, os.str()); break;
        case 178 : texte = (this->*getTextByLangFunc)(679, os.str()); break;
        case 179 : texte = (this->*getTextByLangFunc)(680, os.str());
            buffer = (this->*getTextByLangFunc)(681, os.str()); break;
        case 181 : texte = (this->*getTextByLangFunc)(682, os.str()); break;
        case 182 : texte = (this->*getTextByLangFunc)(683, os.str()); break;
        case 183 : texte = (this->*getTextByLangFunc)(684, os.str()); break;
        case 184 : texte = (this->*getTextByLangFunc)(685, os.str());
            buffer = (this->*getTextByLangFunc)(686, os.str()); break;
        case 186 : texte = (this->*getTextByLangFunc)(687, os.str()); break;
        case 187 : texte = (this->*getTextByLangFunc)(688, os.str());
            buffer = (this->*getTextByLangFunc)(689, os.str()); break;
        
        case 189 : texte = (this->*getTextByLangFunc)(690, os.str()); idsuiv=190; break;
        case 190 : texte = (this->*getTextByLangFunc)(691, os.str()); idsuiv=191; break;
        case 191 : texte = (this->*getTextByLangFunc)(692, os.str()); idsuiv=192; break;
        case 192 : texte = (this->*getTextByLangFunc)(693, os.str()); idsuiv=193; break;
        case 193 : texte = (this->*getTextByLangFunc)(694, os.str()); idsuiv=194; break;
        case 194 : texte = (this->*getTextByLangFunc)(695, os.str()); idsuiv=195; break;
        case 195 : texte = (this->*getTextByLangFunc)(696, os.str()); break;
        
        
        case 196 : 
            if (gpJeu->getJoueur()->getCoeur(43)) {
                if (gpJeu->getJoueur()->nbEnnemis() >= 46) {id=205; chercheText();return;}
                else {id=204; chercheText();return;}
            }
            for (int i = 38; i < 44; i++) 
                if (!gpJeu->getJoueur()->getCoeur(i) 
                && (gpJeu->getJoueur()->nbEnnemis()/7)+37>=i) {
                    id=203; chercheText();return;
                }
            tmp = 7-(gpJeu->getJoueur()->nbEnnemis()%7);
            os << tmp;
            if (tmp>1) texte = (this->*getTextByLangFunc)(697, os.str());
            else texte = (this->*getTextByLangFunc)(698, os.str());
            break;
        case 203 : texte = (this->*getTextByLangFunc)(699, os.str()); break;
        case 204 : texte = (this->*getTextByLangFunc)(700, os.str()); break;
        case 205 : texte = (this->*getTextByLangFunc)(701, os.str()); break;
        
        case 206 : texte = (this->*getTextByLangFunc)(702, os.str()); break;
        case 207 : texte = (this->*getTextByLangFunc)(703, os.str()); break;
        case 208 : texte = (this->*getTextByLangFunc)(704, os.str()); break;
        case 209 : texte = (this->*getTextByLangFunc)(705, os.str()); break;
        case 210 : texte = (this->*getTextByLangFunc)(706, os.str()); break;
        case 211 : texte = (this->*getTextByLangFunc)(707, os.str()); break;
        case 212 : texte = (this->*getTextByLangFunc)(708, os.str()); break;
        case 213 : texte = (this->*getTextByLangFunc)(709, os.str()); break;
        case 214 : texte = (this->*getTextByLangFunc)(710, os.str()); break;
        
        case 215 :texte = (this->*getTextByLangFunc)(711, os.str()); break;
        case 216 :texte = (this->*getTextByLangFunc)(712, os.str()); break;
        case 217 :texte = (this->*getTextByLangFunc)(713, os.str()); break;
        
        case 223 : texte = (this->*getTextByLangFunc)(714, os.str());
            buffer = (this->*getTextByLangFunc)(715, os.str()); break;
        case 224 : texte = (this->*getTextByLangFunc)(716, os.str()); break;
        case 225 : texte = (this->*getTextByLangFunc)(717, os.str()); break;
        case 226 : texte = (this->*getTextByLangFunc)(718, os.str()); break;
        case 227 : texte = (this->*getTextByLangFunc)(719, os.str()); break;
        
        case 228 : texte = (this->*getTextByLangFunc)(720, os.str()); idsuiv = 229; break;
        case 229 : texte = (this->*getTextByLangFunc)(721, os.str()); idsuiv = 230; break;
        case 230 : texte = (this->*getTextByLangFunc)(722, os.str()); idsuiv=231; break;
        case 231 : texte = (this->*getTextByLangFunc)(723, os.str()); idsuiv=232; break;
        case 232 : texte = (this->*getTextByLangFunc)(724, os.str()); 
            buffer=(this->*getTextByLangFunc)(725, os.str()); break;
        case 233 : texte = (this->*getTextByLangFunc)(726, os.str()); idsuiv = 234; break;
        case 234 : texte = (this->*getTextByLangFunc)(727, os.str()); idsuiv=235; break;
        case 235 : texte = (this->*getTextByLangFunc)(728, os.str()); break;
        case 236 : texte = (this->*getTextByLangFunc)(729, os.str()); break;
    }
    
    
}

// Affiche un caractère, retourne la taille prise par le caractère et modifie l'index i dans la chaine de caractère.
int Texte::afficheCaractere(SDL_Surface* gpScreen, char character, int &i, std::string s, int a, int b) {
    int stringLength = (int)s.length();
    int valCharacter = (int)character;
        
#ifdef __vita__
    // Playstation button
    // ¾1 => Triangle
    // ¾2 => Rond
    // ¾3 => Croix
    // ¾4 => Carré
    // ¾5 => Pad Droite
    // ¾6 => Pad Haut
    // ¾7 => Pad Gauche
    // ¾8 => Pad Bas
    // ¾9 => Stick analogique
    if (valCharacter == 190){
        int buttonIndex = 0;
        char nextCharacter;
        int nextCharacterValue;
        do {
            i++;
            nextCharacter = s.at(i);
            nextCharacterValue = (int)nextCharacter;
            if (nextCharacterValue <48 || nextCharacterValue>57){
                i--;
                break;
            }

            buttonIndex+= nextCharacterValue - 48;
        }
        while(nextCharacter < stringLength);
        affichePSBouton(gpScreen, buttonIndex, a, b);
        return 14;
    }
    else {
#endif
        afficheLettre(gpScreen, character,a,b);
        return 6;
#ifdef __vita__
    }
#endif
}

void Texte::affiche(SDL_Surface* gpScreen, std::string s, int a, int b) {
    int stringLength = (int)s.length();
    for (int i = 0; i < stringLength; i++) {
        a+=afficheCaractere(gpScreen, s.at(i), i, s, a, b);
    }
}

void Texte::afficheTexteAvecId(SDL_Surface* gpScreen, int id, std::string s, int a, int b) {
    std::string texte = (this->*getTextByLangFunc)(id, s);
    affiche(gpScreen, texte, a, b);
}

void Texte::draw(SDL_Surface* gpScreen) {
    
    if (cadre) drawCadre(gpScreen);
    
    if (id==3) {
        SDL_Rect src; SDL_Rect dst;
        src.x=16*(gpJeu->getJoueur()->nbQuarts()%4);
        if(src.x==0)src.x=16*4;
        src.y=0; src.w=16; src.h=16; dst.x=160-8; dst.y=120-8+16*5;
        SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
    }
    
    int a = x+8; int b = y+8;
    for (int i = 0; i < av; i++) {
        a+=afficheCaractere(gpScreen, texte.at(i), i, texte, a, b);;
        if (a > x+w-16) {a=x+8; b+=16;}
    }
    
    if(SDL_GetTicks() > lastAnimTime + vitesse && def && av < (int)texte.length()) {
        lastAnimTime = SDL_GetTicks();
        do av++;
        while (av < (int)texte.length() && texte.at(av-1) == ' ');
        if (texte.at(av-1) != ' ') gpJeu->getAudio()->playSound(0,1);
    }
}

bool Texte::isFinished() {return (av==(int)texte.length());}

int Texte::getId() {return id;}

void Texte::changeId(int i) {
    id=i; idsuiv=0; buffer="";
    chercheText();
    decoupeText();
    if (av>(int)texte.length()) av=(int)texte.length();
}

void Texte::drawCadre(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=8; src.h=8; src.x = 103; src.y = 100; dst.x = x; dst.y = y;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.y = 109; src.w=8;
    for (int j = 8; j < h-8; j+=16) {
        dst.y = y + j;
        src.x = 103; dst.x = x; src.h=16;
        while (dst.y + src.h > y+h && src.h>0) src.h--;
        if (src.h>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
        src.x = 129; dst.x = x+w-8;
        if (src.h>0)SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.h=8; src.x = 103; src.y = 126; dst.x = x; dst.y = y+h-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

void Texte::setTexte(int idTxt, int vx, int vy, int vw, int vh, bool cadr, bool defil, int vit) {
    if (idTxt == 0) return;
    id = idTxt; 
    idsuiv = 0;
    buffer = "";
    chercheText();
    
    x = vx; y = vy; w = vw; h = vh;
    decoupeText();
        
    def=defil;
    if (def) av = 0;
    else av = texte.length();
    
    cadre = cadr;
    
    vitesse = vit;
}

void Texte::decoupeText() {
    //compte le nombre de caractères possibles et largeur et en hauteur
    int nbcol = (w-16)/6 -1;
    int nblig = (h-16)/16;
    int tailleMax = nbcol * nblig;
    int taille;
    
    //parcours du texte à afficher; à chaque début de mot, 
    //vérifie que le mot peut tenir sur la ligne
    for (int i = 0; i < (int)texte.length(); i++) {
        
        //supprime les espaces isolés en début de ligne
        if (texte.at(i)==' ' && texte.at(i+1)!=' ' && i%nbcol == 0) texte.erase(i,1);
        //recherche du début du prochain mot
        while(texte.at(i)==' ' && i < (int)texte.length()-1) i++;
        
        //saute une ligne si trouve une étoile
        if (texte.at(i)=='*') {
            texte.erase(i,1);//replace(i, 1, " ");
            int nb = (nbcol)-(i%(nbcol));
            for (int j = 0; j < nb; j++) texte.insert(i," ");
            continue;
        }
        
        //si le mot dépasse
        taille = tailleMot(i);
        if ((i%nbcol)+taille>nbcol) {
            if  (i < tailleMax) {
                //si le mot ne tient pas sur une ligne, on le coupe avec des tirets
                if (taille>nbcol) {
                    texte.insert(((i/nbcol)+1)*nbcol-1,"--");
                    i = 1+((i/nbcol)+1)*nbcol;
                }
                //sinon, on ajoute des espaces pour faire commencer le mot à la ligne
                else while((i%nbcol) != 0) {texte.insert(i," "); i++;}
            }
        }
        
    }
    
    // si le texte est trop grand, on le coupe en deux
    if ((int)texte.length() > tailleMax) {
        buffer = texte.substr(tailleMax);
        texte = texte.substr(0, tailleMax);
    }
}

int Texte::tailleMot(int deb) {
    int i = deb;
    int total = 0;
    while (texte.at(i)!=' ') {total++; i++; if (i >= (int)texte.length()) return total;}
    return total;
}

void Texte::afficheLettre(SDL_Surface* gpScreen, char c, int vx, int vy) {
    SDL_Surface* img = imageFont;
    SDL_Rect src;
    SDL_Rect dst;
    
    int val = (int)c;
    
    dst.x=vx; dst.y=vy;
    src.h=16;src.w=8;
    
    if(val==32) return;
    
    //minuscules a-z
    if(val>=97 && val<=122) {
		src.x=4+16*((val-97)%10); 
		src.y=52+16*((val-97)/10);
	}
	//majuscules A-Z
	else if(val>=65 && val<=90) {src.x=6+16*((val-65)%10); src.y=2+16*((val-65)/10);}
	//chiffres
    else if(val>=48 && val<=57) {src.x=3+16*((val-48)%5); src.y=103+16*((val-48)/5);}
	else {
		switch(val){
            // ES characters
            // ñ
            case 241:
            case -15: src.x=164;src.y=68; break;
            // ó
            case 243:
            case -13: src.x=164;src.y=103; break;
            // í
            case 237:
            case -19: src.x=164;src.y=52; break;
            // á
            case 225:
            case -31: src.x=164;src.y=84; break;
            // ú
            case 250:
            case -6: src.x=164;src.y=151; break;
			
            // DE characters
            // ß
            case 223:
            case -33: src.x=6+16*3; src.y=167; break;
            // Ä
            case 196:
            case -60: src.x=6; src.y=167; break;            
            // Ö
            case 214:
            case -42: src.x=6+16; src.y=167; break;            
            // Ü
            case 220:
            case -36: src.x=6+16*2; src.y=167; break;
			
            
            // Caractères spéciaux
            // /
			case 47: src.x=52;src.y=151;break;
			// @ hylien
			case 64: src.x=4;src.y=151;break;
            // + hylien
			case 43: src.x=20;src.y=151;break;
            // = hylien
			case 61: src.x=36;src.y=151;break;
			// ç
			case -25:
			case 231: src.x=148;src.y=34;break;
			// é
			case -23: 
			case 233: src.x=100;src.y=84;break;
			// ê
			case -22:
			case 234: src.x=116;src.y=84;break;
			// è
			case -24:
			case 232: src.x=132;src.y=84;break;
			// ë
			case -21:
			case 235: src.x=132;src.y=151;break;
			// à
			case -32:
			case 224: src.x=148;src.y=84;break;
			// â
			case -30:
			case 226: src.x=148;src.y=103;break;
			// ä
			case -28:
			case 228: src.x=148;src.y=135;break;
			// î
			case -18:
			case 238: src.x=84;src.y=119;break;
			// ï
			case -17:
			case 239: src.x=116;src.y=151;break;
			// û
			case -5:
			case 251: src.x=84;src.y=103;break;
			// ù
			case -7:
			case 249: src.x=148;src.y=151;break;
			// ü
			case -4:
			case 252: src.x=116;src.y=135;break;
			// ö
			case -10:
			case 246: src.x=132;src.y=135;break;
			// ô
			case -12:
			case 244: src.x=148;src.y=119;break;
			
			// Ponctuation
			//ponctuation
			// -
			case 45: src.x=102;src.y=34;break;
			// .
			case 46: src.x=118;src.y=34;break;
			// ,
			case 44: src.x=134;src.y=34;break;
			// !
			case 33: src.x=3;src.y=135;break;
			// ?
			case 63: src.x=19;src.y=135;break;
			// (
			case 40: src.x=35;src.y=135;break;
			// )
			case 41: src.x=51;src.y=135;break;            
			// ' ( avec @ )
			case 39: src.x=67;src.y=135;break;
			// :
			case 58: src.x=83;src.y=135;break;
			// ... ( avec % )
			case 37: src.x=101;src.y=135;break;
			// >
			case 60: src.x=100;src.y=151;break;
			// <
			case 62: src.x=84;src.y=151;break;
		}
	}
    
    SDL_BlitSurface(img, &src, gpScreen, &dst);
}

void Texte::affichePSBouton(SDL_Surface* gpScreen, int index, int vx, int vy) {
    SDL_Surface* img = imageButtons;
    SDL_Rect src;
    SDL_Rect dst;
    
    dst.x=vx; dst.y=vy;
    
    // Playstation button
    // 1 => Triangle
    // 2 => Rond
    // 3 => Croix
    // 4 => Carré
    // 5 => Pad Droite
    // 6 => Pad Haut
    // 7 => Pad Gauche
    // 8 => Pad Bas
    // 9 => Stick analogique
	switch(index){
        case 1: 
            src.x=2;
            src.y=2;
            src.h=16;
            src.w=16;
            break;
        case 2: 
            src.x=22;
            src.y=2;
            src.h=16;
            src.w=16;
            break;
        case 3: 
            src.x=42;
            src.y=2;
            src.h=16;
            src.w=16;
            break;
        case 4: 
            src.x=62;
            src.y=2;
            src.h=16;
            src.w=16;
            break;
        case 5:
            src.x=2;
            src.y=24;
            src.h=12;
            src.w=16;
            dst.y+=2;
            break;
        case 6:
            src.x=24;
            src.y=22;
            src.h=16;
            src.w=12;
            dst.y+=2;
            break;
        case 7:
            src.x=42;
            src.y=24;
            src.h=12;
            src.w=16;
            dst.y+=2;
            break;
        case 8:
            src.x=64;
            src.y=22;
            src.h=16;
            src.w=12;
            dst.y+=2;
            break;
        case 9:
            src.x=2;
            src.y=42;
            src.h=16;
            src.w=16;
            break;
	}
    
    SDL_BlitSurface(img, &src, gpScreen, &dst);
}

bool Texte::hasNext() {
    return (buffer != "" || idsuiv > 0);
}

bool Texte::suite() {
    if (av < (int)texte.length()) {
        av = texte.length();
        return true;
    }
    if (!hasNext()) {
        gpJeu->getAudio()->playSound(18);
        return gpJeu->finTexte(id);
    }
    if (buffer != "") {
        texte = buffer;
        buffer = "";
    }
    else {
        id = idsuiv;
        idsuiv = 0;
        chercheText();
    }
    decoupeText();
    if (def) av = 0;
    else av = texte.length();
    gpJeu->getAudio()->playSound(17);
    return true;
}
