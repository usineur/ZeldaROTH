/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

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
    imageCoeur = gpJeu->loadImg("data/images/menu/coeur.png");
    SDL_SetColorKey(imageCoeur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCoeur->format,0,0,255));
}

Texte::~Texte() {
    SDL_FreeSurface(imageFont);
    SDL_FreeSurface(imageCoeur);
}

void Texte::chercheText() {
    ostringstream os;
    int tmp;
    switch (id) {
        case 1  : texte = "Tu as trouvé un bouclier !!!**Ta défense augmente d'un point !"; break;
        case 2  : texte = "Tu as trouvé une épée !!!**Tu vas pouvoir te défendre face aux monstres avec la touche W (ou Z) !!!*Maintiens W enfoncé pour charger une attaque cyclone !!!"; break;
        case 3  : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = "Tu as trouvé un quart de coeur !!!";
            if (tmp<4) buffer = "Encore "+os.str()+" et tu gagneras un coeur supplémentaire !!!";
            else buffer = "Ton nombre de coeurs vient d'augmenter !!!";
            break;
        case 11 : texte = "N : Maison de Link*O : Plaine d'Hyrule*E : Temple de la Forêt"; break;
        case 12 : texte = "Temple de la Montagne**Déconseillé aux cardiaques, peureux, et aux âmes sensibles en général."; break;
        case 13 : texte = "O : Entrée du Désert*N : Temple de la Montagne"; break;
        case 14 : texte = "N : Temple de la Montagne*S : Plaine d'Hyrule"; break;
        case 15 : texte = "N : Mont du Péril"; break;
        case 16 : texte = "E : Entrée de la Forêt"; break;
        case 17 : texte = "S : Lac Hylia*E : Cimetière Hanté"; break;
        case 18 : texte = "S : Vers le Village Cocorico"; break;
        case 19 : texte = "N : Village Cocorico"; break;
        case 20 : texte = "N : Plaine d'Hyrule"; break;
        case 21 : texte = "O : Terres de Feu"; break;
        case 22 : texte = "E : Village de l'Ombre*- Déconseillé aux vivants -"; break;
        case 23 : texte = "Temple des Ténèbres**Si vous êtes un fantôme et que vous cherchez un job, venez plutôt chômer ici."; break;
        case 24 : texte = "N : Village de l'Ombre*O : Lac Hylia"; break;
        case 25 : texte = "N : Cimetière Hanté**Entrée interdite"; break;
        case 26 : texte = "Village de l'Ombre"; break;
        case 27 : texte = "Je vends un flacon pour 100 rubis, ça t'intéresse ?*              OUI ?            non  "; 
            if ((gpJeu->getJoueur()->hasBouteille(0) && gpJeu->getZone()==8)
            || (gpJeu->getJoueur()->hasBouteille(1) && gpJeu->getZone()==5)
            || (gpJeu->getJoueur()->hasBouteille(2) && gpJeu->getZone()==6)) {id=32; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) idsuiv=29;
            else idsuiv=30;
            break;
        case 28 : texte = "Je vends un flacon pour 100 rubis, ça t'intéresse ?*              oui              NON ?"; idsuiv=31; break;
        case 29 : texte = "Désolé, mais tu n'as pas assez de rubis."; break;
        case 30 : texte = "Merci beaucoup, voilà ton flacon."; break;
        case 31 : texte = "Reviens me voir si tu changes d'avis."; break;
        case 32 : texte = "Désolé, c'était mon seul flacon."; break;
        case 33 : texte = "Tu as trouvé un flacon vide !!!**Tu vas pouvoir t'en servir pour stocker des potions !!!"; break;
        case 35 : texte = "Les habitants de ce village ont un dialecte très particulier, je n'y comprends rien..."; break;
        case 36 : texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 37 : texte = "Obtiens une autorisation du chef si tu veux vraiment passer!!!"; break;
        case 38 : texte = "Le chef t'as autorisé à passer ??? Grrrr... Alors écarte toi!!!"; break;
        case 39 : texte = "Ne traîne pas dans mes pattes !!!"; break;
        case 40 : texte = "On n'a pas l'habitude de voir des visiteurs par ici..."; break;
        case 41 : texte = "Les monstres du coin ne craignent pas grand chose, heureusement qu'ils n'attaquent que les humains."; break;
        case 42 : texte = "C'est vrai ?*Tu comprends ce que je dis ?"; break;
        case 43 : texte = "N : Désert et Village Gerudo"; break;
        case 44 : texte = "S : Lac Hylia*O : Château d'Hyrule"; break;
        case 45 : texte = "Village Cocorico"; break;
        case 46 : texte = "O : Château d'Hyrule"; break;
        case 47 : texte = "Quelle belle journée !!!"; break;
        case 48 : texte = "Pourquoi ai-je accepté de m'occuper de ces saletés ???*J'ai horreur des poules !!!"; break;
        case 49 : texte = "On trouve des tas de choses dans les boutiques du village."; break;
        case 50 : texte = "S : Village Cocorico*O : Désert*E : Mont du Péril"; break;
        case 51 : texte = "Village Gerudo"; break;
        case 52 : texte = "Perdu dans le désert ?*Vous êtes ici :*                        X"; break;
        case 54 : texte = "S : Vers le Château d'Hyrule"; break;
        case 55 : texte = "Temple du Désert**Venez essayer nos bains.*(eau non-potable)"; break;
        case 56 : texte = "Temple de la Forêt**Sauvez les arbres, mangez du castor!!!"; break;
        case 57 : texte = "Temple du Lac**Bonnet de bain obligatoire."; break;
        case 58 : texte = "Temple de Glace**Le personnel tient à rappeler qu'un donjon n'est pas une patinoire."; break;
        case 59 : texte = "As-tu été voir le forgeron de ce village ?*On dit qu'il est très doué pour améliorer l'équipement des aventuriers, beaucoup de monde lui rend visite."; break;
        case 60 : texte = "Le temple se trouve au fin fond du désert, à la place d'une ancienne oasis."; break;
        case 61 : texte = "S : Terres de Feu*E : Village Cocorico"; break;
        case 62 : texte = "Château d'Hyrule"; break;
        case 63 : texte = "E : Village Cocorico"; break;
        case 64 : texte = "O : Roc de la Tortue*E : Lac Hylia"; break;
        case 65 : texte = "Temple Caché**Ici repose la lame purificatrice, Excalibur."; break;
        case 66 : texte = "N : Vers le cimetière hanté"; break;
        case 67 : texte = "Tu as trouvé la carte du donjon !!!*Appuie sur P pour voir le plan."; break;
        case 68 : texte = "Tu as trouvé la boussole !!!*Tu peux localiser le boss et les coffres sur le plan."; break;
        case 69 : texte = "Tu as trouvé la clé du boss !!!"; break;
        case 70 : texte = "Tu as trouvé une petite clé !!!*Approche une porte pour l'ouvrir."; break;
        case 71 : texte = "Tu as trouvé les gants !!!*Utilise-les pour soulever des objets en les équipant ou en appuyant sur C."; break;
        case 72 : 
            texte = "Tu as trouvé un cristal magique !!!"; 
            tmp = 7-gpJeu->getJoueur()->nbCristaux();
            os << tmp;
            if (tmp==6 && !gpJeu->getJoueur()->getAvancement()) buffer = "A quoi pourra-t-il bien servir ?";
            else if (tmp>2) buffer = "Il en reste encore "+os.str()+" à trouver !!!";
            else if (tmp==2) buffer = "Plus que 2 à trouver !!!";
            else if (tmp==1) buffer = "Il ne t'en manque plus qu'un seul !!!";
            else if (tmp==0) buffer = "Tu as tous les cristaux, cours au château sauver Zelda !!!";
            break;
        case 80 : texte = "Tu as trouvé le grappin !!!*Utilise-le pour franchir des obstacles."; break;
        case 81 : texte = "Tu as trouvé la lanterne !!!*Utilise-la pour faire jaillir des flammes."; break;
        case 82 : texte = "Tu as trouvé les palmes !!!*Equipe-les pour aller dans l'eau."; break;
        case 83 : texte = "Tu as trouvé le marteau magique !!!*Utilise-le pour écraser les obstacles."; break;
        case 84 : texte = "Tu as trouvé le baton de feu !!!*Tu peux désormais lancer de puissantes flammes à distance."; break;
        case 85 : texte = "Tu as trouvé le baton de glace !!!*Utilise-le pour tout congeler à distance."; break;
        case 86 : texte = "Tu as trouvé Excalibur !!!*Même Ganon ne devrait pas pouvoir résister à sa puissance !!! (en théorie)"; break;
        case 87 : texte = "Félicitation Link, tu as réussi à venir me délivrer!!!***Allons vite trouver Ganon, il faut impérativement lui reprendre la Triforce !"; break;
        case 89 : texte = "Le passage secret derrière la salle du trône mène à Ganon. Dépêchons-nous !"; break;
        case 90 : texte = "Nous y sommes presque, suis-moi !"; break;
        case 91 : texte = "J'ai bien peur que tu ne puisses jamais vaincre Ganon avec tes armes actuelles...*Va parler au chef du village Cocorico, je suis sûre qu'il trouvera une solution."; break;
        case 92 : texte = "Ganon est juste derrière cette porte, je vais soigner tes blessures."; break;
        case 93 : texte = "Ganon est toujours quelque part dans le château."; break;
        case 94 : texte = "Tu devrais attendre la princesse Zelda !!!"; break;
        case 95 : texte = "Tu n'aurais pas l'étrange sentiment d'oublier quelqu'un par hasard ???"; break;
        case 96 : texte = "Zelda t'attend!!!"; break;
        case 97 : texte = "Tu as trouvé la Triforce!!!"; break;
        case 98 : texte = "Tu as trouvé le livre de Mudora!!!**Tu comprends désormais le Hylien ancien!!!"; break;
        case 99 : texte = "Félicitation Link, tu as réussi à me trouver. En récompense, je t'offre le médaillon de Din, il augmente ta défense d'un point."; break;
        case 100 : texte = "Félicitation Link, tu as réussi à me trouver. En récompense, je t'offre le médaillon de Nayru, il augmente ta défense de deux points!!!"; break;
        case 101 : texte = "..."; break;
        case 102 : texte = "Tu as obtenu un médaillon magique !!!**Ta défense vient d'augmenter!!!"; break;
        case 103 : texte = "Félicitation Link, tu as réussi à me trouver. Pour te récompenser, je vais doubler la capacité de ta réserve de magie!!!"; break;
        case 104 : texte = "Ta réserve de magie a doublé!!!"; break;
        case 105 : texte = "Reviens me voir quand tu auras un flacon vide  et je te vendrai une potion rouge qui restaure l'énergie."; break;
        case 106 : texte = "Une potion rouge pour 60 rubis, ça t'intéresse?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=105; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=29;
            else idsuiv=108; break;
        case 107 : texte = "Une potion rouge pour 60 rubis, ça t'intéresse?*              oui              NON ?"; break;
        case 108 : texte = "Merci, voilà ta potion.";break;
        case 109 : texte = "Tu as obtenu une potion rouge !!!*Bois-la pour restaurer ton énergie!!!"; break;
        case 110 : texte = "Tu as obtenu une potion verte !!!*Bois-la pour restaurer ta magie!!!"; break;
        case 111 : texte = "Tu as obtenu une potion bleue !!!*Bois-la pour restaurer ton énergie et ta magie!!!"; break;
        case 112 : texte = "Bonjour, je vous sers quelque chose ?"; break;
        case 113 : texte = "Hic! On raconte qu'une fée donnerait des objets enchantés... Hic! ...aux aventuriers qui la  trouveraient... Hic!!!"; break;
        case 114 : texte = "Un coeur pour 10 rubis, ok ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getVie()+gpJeu->getJoueur()->getBoostVie()
            == gpJeu->getJoueur()->getVieMax()) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=29;
            else idsuiv=129; break;
        case 115 : texte = "Un coeur pour 10 rubis, ok ?**              oui              NON ?"; break;
        case 116 : texte = "Un peu de magie pour 20 rubis, ok ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getMagie()+gpJeu->getJoueur()->getBoostMagie()
            == gpJeu->getJoueur()->getMagieMax() || !gpJeu->getJoueur()->hasObjet(O_LANTERNE)) {
                id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=29;
            else idsuiv=129; break;
        case 117 : texte = "Un peu de magie pour 20 rubis, ok ?**              oui              NON ?"; break;
        case 118 : texte = "Beaucoup de magie pour 30 rubis, ok ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getMagie()+gpJeu->getJoueur()->getBoostMagie()
            == gpJeu->getJoueur()->getMagieMax() || !gpJeu->getJoueur()->hasObjet(O_LANTERNE)) {
                id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 119 : texte = "Beaucoup de magie pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 120 : texte = "5 flèches pour 30 rubis, ok ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax() 
            || !gpJeu->getJoueur()->hasObjet(O_ARC)) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 121 : texte = "5 flèches pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 122 : texte = "Une bombe pour 30 rubis, ok ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax() 
            || !gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 123 : texte = "Une bombe pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 124 : texte = "Un arc pour 1000 rubis, ok ?**              OUI ?            non  "; 
            idsuiv=29; break;
        case 125 : texte = "Un arc pour 1000 rubis, ok ?**              oui              NON ?"; break;
        case 126 : texte = "Un arc pour 50 rubis, ok ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<50) idsuiv=29;
            else idsuiv=129; break;
        case 127 : texte = "Un arc pour 50 rubis, ok ?**              oui              NON ?"; break;
        case 128 : texte = "Tu n'as pas besoin de ça maintenant."; break;
        case 129 : texte = "Merci."; break;
        case 130 : texte = "Tu as obtenu l'arc !!!*Utilise-le pour atteindre des cibles éloignées."; break;
        case 131 : texte = "Choisis ce que tu veux."; break;
        case 132 : texte = "Hein ???*Tu es en mission pour le chef ???*Bon alors je vais te faire une réduction sur l'arc..."; break;
        case 133 : texte = "Bonjour Link, je suis le chef de ce village, je me doutais que tu passerais."; idsuiv=134; break;
        case 134 : texte = "Depuis ce matin des monstres sont apparus un peu partout à Hyrule, j'ai voulu aller en parler à la princesse Zelda, mais comme tu l'as peut-être déjà vu, un puissant sortilège bloque l'accès au château..."; idsuiv=136; break;
        case 136 : texte = "Tu dis que Ganon est responsable de tout ça ? Qu'il a volé la Triforce et qu'il détient la princesse Zelda prisonnière ?"; idsuiv=137; break;
        case 137 : texte = "Mmmm... la situation est plus grave que je le croyais..."; idsuiv=138; break;
        case 138 : texte = "Il faut agir au plus vite, tu dois affronter Ganon à nouveau!"; idsuiv=139; break;
        case 139 : texte = "Comment entrer dans le château ? J'ai peut-être une idée..."; idsuiv=140; break;
        case 140 : texte = "Comme tu le sais, le pouvoir des 7 sages a été enfermé dans 7 cristaux par le sorcier Aghanim alors qu'il tentait de lever le sceau qui confinait Ganon au monde des ténèbres."; idsuiv=141; break;
        case 141 : texte = "Or, bien que tu aies ressuscité les descendants des sages après avoir vaincu Ganon et trouvé la Triforce, ces cristaux ont conservé leur puissance."; idsuiv=142; break;
        case 142 : texte = "Ils ont été cachés au fin fond des 7 temples, réunis-les tous et tu pourras passer outre le sortilège de Ganon."; idsuiv=143; break;
        case 143 : texte = "Ce ne sera toutefois pas chose aisé, Ganon a certainement dû envoyer ses meilleurs éléments protéger ces cristaux..."; idsuiv=144; break;
        case 144 : texte = "Une dernière chose, tu n'iras pas loin avec ton équipement actuel. Va voir le marchand d'armes et dis-lui que tu viens de ma part. Il fera sûrement un geste pour toi."; break;
        case 145 : texte = "Va voir le marchand d'armes et dis-lui que tu viens de ma part, il fera certainement un geste pour toi."; break;
        case 146 : texte = "Il te faut rassembler les 7 cristaux pour avoir une chance de sauver Zelda et Hyrule..."; break;
        case 147 : texte = "Tu as trouvé les 7 cristaux ? Alors rends-toi au château, tu dois avant tout délivrer la princesse, elle saura mieux que moi comment sauver Hyrule."; break;
        case 148 : texte = "Tes armes sont sans effet sur Ganon ? Dans ce cas tu dois trouver Excalibur. On raconte qu'elle a été dissimulée dans un temple caché.*On dit aussi que le chemin menant à la lame purificatrice passe par un village peuplé de monstres...*Je me demande si un tel village existe..."; break;
        case 150 : texte = "Toutefois j'ai bien peur que ton équipement actuel soit insuffisant pour accéder à ce temple, tu devrais peut-être passer voir le forgeron du village Gerudo..."; break;
        case 151 : texte = "Il est temps d'affronter Ganon et de lui reprendre la Triforce!"; break;
        case 152 : texte = "Hey! Il faut payer pour ouvrir un de mes coffres!!!"; break;
        case 153 : texte = "Un de ces coffres contient un quart de coeur, tu veux tenter ta chance pour 10 rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=29; break;
        case 154 : texte = "Un de ces coffres contient un quart de coeur, tu veux tenter ta chance pour 10 rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?*              oui              NON ?"; break;
        case 155 : texte = "Choisis un coffre."; break;
        case 156 : texte = "Je n'ai plus de prix à mettre en jeu, désolé."; break;
        case 157 : texte = "Perdu! Ce coffre est vide."; break;
        case 158 : texte = "Bonjour! Si vous êtes venu voir le forgeron, il habite un peu plus loin."; break;
        case 159 : texte = "Bonjour Link, je suis le chef de ce village.*Tu devrais aller voir le forgeron et lui présenter ce que tu veux qu'il reforge dans ton équipement.";
            buffer = "J'ai été informé de ta quête, alors je me suis arrangé avec lui.*Tout sera gratuit pour toi."; break;
        case 160 : texte = "Tu n'as pas besoin de boire cette potion maintenant."; break;
        case 161 : texte = "Une potion verte pour 40 rubis, ça t'intéresse?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=163; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=29;
            else idsuiv=108; break;
        case 162 : texte = "Une potion verte pour 40 rubis, ça t'intéresse?*              oui              NON ?"; break;
        case 163 : texte = "Reviens me voir quand tu auras un flacon vide et je te vendrai une potion verte qui restaure la magie."; break;
        case 164 : texte = "Reviens plus tard, je suis débordé!"; break;
        case 165 : texte = "Puis-je faire quelque chose pour toi ?";
            if (gpJeu->getJoueur()->getEpee()==1) {id=166; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_GANTS)==1 && gpJeu->getJoueur()->getObjet()==8) {
                id=169; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_ARC)==2 && gpJeu->getJoueur()->getObjet()==0 
            && gpJeu->getJoueur()->nbCristaux()==7) {
                id=172; chercheText();break;}
            break;
        case 166 : texte = "Veux-tu que je reforge ton épée ?**              OUI ?            non  "; break;
        case 167 : texte = "Veux-tu que je reforge ton épée ?**              oui              NON ?"; break;
        case 168 : texte = "Ton épée a triplé de puissance et peut désormais renvoyer certaines attaques magiques, trop bien !!!*"; break;
        case 169 : texte = "Veux-tu que j'améliore tes gants ?**              OUI ?            non  "; break;
        case 170 : texte = "Veux-tu que j'améliore tes gants ?**              oui              NON ?"; break;
        case 171 : texte = "La puissance de tes gants va te permettre de soulever de lourds rochers."; break;
        case 172 : texte = "Veux-tu que j'améliore ton arc ?**              OUI ?            non  "; break;
        case 173 : texte = "Veux-tu que j'améliore ton arc ?**              oui              NON ?"; break;
        case 174 : texte = "Ton arc tire désormais des flèches d'argent d'une puissance dévastatrice!!!"; break;
        case 175 : texte = "Reviens me voir quand tu auras un flacon vide et je te vendrai une potion bleue qui restaure l'énergie et la magie."; break;
        case 176 : texte = "Une potion bleue pour 160 rubis, ça t'intéresse?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=175; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=29;
            else idsuiv=108; break;
        case 177 : texte = "Une potion bleue pour 160 rubis, ça t'intéresse?*              oui              NON ?"; break;
        case 178 : texte = "Notre village a été fondé pour empêcher les aventuriers imprudents d'accéder au temple, je ne donne pas l'autorisation de passer à n'importe qui."; break;
        case 179 : texte = "Mmmm... Tu as déjà trouvé 4 cristaux ?*Je dois avouer que tu m'impressionnes...";
            buffer = "Bon c'est entendu, tu as l'autorisation de passer par le cimetière, à tes risques et périls."; break;
        case 181 : texte = "Va parler au garde au nord du village, il te laissera passer."; break;
        case 182 : texte = "Je vois que tu es toujours vivant...*Etonnant."; break;
        case 183 : texte = "Le temple de l'ombre constitue le point de départ du chemin menant à un objet de légende. Ce village ne sert qu'à dissuader les aventuriers de trop s'en approcher."; break;
        case 184 : texte = "Ainsi tu as trouvé l'Epée ?*Mais ne crois pas qu'elle soit à toi pour autant.";
            buffer = "Excalibur fait partie du patrimoine le plus précieux d'Hyrule avec la Triforce, tu devras la ramener dans son sanctuaire une fois ta mission achevée."; break;
        case 186 : texte = "Les habitants de ce village sont tous des esprits ayant répondu à l'appel de la princesse Zelda."; break;
        case 187 : texte = "Lorsque tu as ramené la paix sur Hyrule et réunifié le monde de la lumière avec la Terre d'Or, Zelda a secrètement demandé aux esprits volontaires de créer ce village pour bloquer";
            buffer = "l'accès à un objet de très grande valeur."; break;
        
        case 189 : texte = "Bienvenue Link!*Laisse-moi t'expliquer ce que je fais ici."; idsuiv=190; break;
        case 190 : texte = "Comme tu l'as certainement remarqué, des monstres sont apparus partout dans Hyrule. C'est la première fois que je vois des monstres depuis que tu as vaincu Ganon."; idsuiv=191; break;
        case 191 : texte = "Et bien j'ai décidé de tous les répertorier."; idsuiv=192; break;
        case 192 : texte = "L'ennui c'est que je suis bien trop peureux pour aller à leur rencontre, alors j'ai besoin de ton aide."; idsuiv=193; break;
        case 193 : texte = "Il faut que tu battes chaque type de monstre et que tu viennes me faire ton rapport."; idsuiv=194; break;
        case 194 : texte = "Je te récompenserai tous les 7 nouveaux types d'ennemis vaincus."; idsuiv=195; break;
        case 195 : texte = "Si tu veux savoir quels ennemis tu as déjà vaincu, appuye sur M."; break;
        
        
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
            if (tmp>1) texte = "Encore "+os.str()+" ennemis différents avant la prochaine récompense.";
            else texte = "Plus qu'un nouvel ennemi avant la prochaine récompense!!!";
            break;
        case 203 : texte = "Accepte ce cadeau pour ta contribution à mon projet :"; break;
        case 204 : texte = "Je suis désolé mais je n'ai plus rien à t'offrir..."; break;
        case 205 : texte = "Je n'en crois pas mes yeux, tu as réussi à vaincre chaque type d'ennemis !!!*Félicitation Link!!!"; break;
        
        case 206 : texte = "                   Niveau 1 :**               Temple de la forêt"; break;
        case 207 : texte = "                   Niveau 2 :**                 Temple de l'eau"; break;
        case 208 : texte = "                   Niveau 3 :**              Temple de la montagne"; break;
        case 209 : texte = "                   Niveau 4 :**                Temple du désert"; break;
        case 210 : texte = "                   Niveau 5 :**                Temple de l'ombre"; break;
        case 211 : texte = "                   Niveau 6 :**                  Temple du feu"; break;
        case 212 : texte = "                   Niveau 7 :**                Temple de la glace"; break;
        case 213 : texte = "                   Niveau ? :**                   Temple secret"; break;
        case 214 : texte = "                 Niveau Final :**                Château d'Hyrule"; break;
        
        case 215 :texte = "                Déjà fatigué ?                  ?                CONTINUER                  ?             Sauvegarder et quitter                        Quitter sans sauvegarder           "; break;
        case 216 :texte = "                Déjà fatigué ?                                   Continuer                     ?          SAUVEGARDER ET QUITTER           ?            Quitter sans sauvegarder           "; break;
        case 217 :texte = "                Déjà fatigué ?                                   Continuer                                Sauvegarder et quitter              ?         QUITTER SANS SAUVEGARDER          ?"; break;
        
        case 223 : texte = "A l'instant où Link toucha la Triforce, les monstres disparurent et la paix revint.**La princesse Zelda prit alors une grande décision: elle toucha à son tour la Triforce pour exaucer son voeu...**La Triforce fut depuis toujours à l'origine des problèmes survenus au Royaume, tôt ou tard un autre être malfaisant aurait fini par la trouver.**A la seconde où la princesse toucha la relique, elle disparue à jamais d'Hyrule.";
            buffer = "Depuis ce jour, le peuple d'Hyrule vécut en paix, sans craindre de nouveaux désastres.**Ainsi s'achève la légende de Zelda, celle de la  Triforce et de la Terre d'Or.**On dit que l'épée Excalibur repose en sûreté quelque part, et qu'elle constitue le dernier souvenir de la quête de Link..."; break;
        case 224 : texte = "Félicitation Link, tu as réussi à me trouver. En récompense, je t'offre le médaillon de Farore, il augmente ta défense d'un point."; break;
        case 225 : texte = "Souhaites-tu sauvegarder ta partie ?**                    ? OUI ?*                      non  "; break;
        case 226 : texte = "Souhaites-tu sauvegarder ta partie ?**                      oui  *                    ? NON ?"; break;
        case 227 : texte = "Partie sauvegardée."; break;
        
        case 228 : texte = "Le Royaume d'Hyrule était en paix depuis que Link, dernier chevalier hylien, avait vaincu le maléfique Ganon et lui avait repris la précieuse Triforce."; idsuiv = 229; break;
        case 229 : texte = "Nul ne sait quel voeu fit Link en touchant la Triforce, mais il eut comme effet de réunifier le monde de la lumière et celui des ténèbres, et ramena à la vie les descendants des 7 sages."; idsuiv = 230; break;
        case 230 : texte = "Link remit ensuite à la princesse Zelda la Triforce et l'épée Excalibur, et le peuple se mit à croire que la paix durerait.*Mais le peuple se trompait..."; idsuiv=231; break;
        case 231 : texte = "Le souhait de Link à la Triforce eu hélas de fâcheux effets. Ganon et ses sbires furent ainsi ressuscités et s'apprêtèrent à attaquer."; idsuiv=232; break;
        case 232 : texte = "Quelque part dans la forêt d'Hyrule, Link dort sans se douter que Ganon est passé à l'attaque, jusqu'à ce qu'"; 
            buffer="une voix familière lui parle dans son sommeil..."; break;
        case 233 : texte = "A l'aide!*A l'aide!*C'est moi! C'est Zelda!*Je te parle par télépathie."; idsuiv = 234; break;
        case 234 : texte = "Je suis retenue prisonnière dans le donjon du château! J'ai besoin de ton aide!*Ganon est de retour, et il a certainement dû trouver la Triforce à l'heure qu'il est..."; idsuiv=235; break;
        case 235 : texte = "Viens vite au château Link, tu es mon seul espoir..."; break;
        case 236 : texte = "AIDE : Appuie sur F1 pour consulter l'aide."; break;
    }
    
    
}

void Texte::affiche(SDL_Surface* gpScreen, std::string s, int a, int b) {
    for (int i = 0; i < (int)s.length(); i++) {
        afficheLettre(gpScreen, s.at(i),a,b);
        a+=6;
    }
}

void Texte::draw(SDL_Surface* gpScreen) {
    
    if (cadre) drawCadre(gpScreen);
    
    if (id==3 && texte == "Tu as trouvé un quart de coeur !!!") {
        SDL_Rect src; SDL_Rect dst;
        src.x=16*(gpJeu->getJoueur()->nbQuarts()%4);
        if(src.x==0)src.x=16*4;
        src.y=0; src.w=16; src.h=16; dst.x=160-8; dst.y=120-8+16*5;
        SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
    }
    
    int a = x+8; int b = y+8;
    for (int i = 0; i < av; i++) {
        afficheLettre(gpScreen, texte.at(i),a,b);
        a+=6;
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
    SDL_Rect src;
    SDL_Rect dst;
    
    int val = (int)c;
    
    dst.x=vx; dst.y=vy;
    src.h=16;src.w=8;
    
    if(val==32) return;
    
    // /
    if(val==47) {src.x=52;src.y=151;}
    
    // @ hylien
    if(val==64) {src.x=4;src.y=151;}
            
    // + hylien
    if(val==43) {src.x=20;src.y=151;}
            
    // = hylien
    if(val==61) {src.x=36;src.y=151;}
            
    //minuscules a-z
    if(val>=97 && val<=122) {src.x=4+16*((val-97)%10); src.y=52+16*((val-97)/10);}
            
    //majuscules A-Z
    if(val>=65 && val<=90) {src.x=6+16*((val-65)%10); src.y=2+16*((val-65)/10);}   
    // ç
    if(val==-25) {src.x=148;src.y=34;}
    // é
    if(val==-23) {src.x=100;src.y=84;}
    // ê
    if(val==-22) {src.x=116;src.y=84;}
    // è
    if(val==-24) {src.x=132;src.y=84;}
    // ë
    if(val==-21) {src.x=132;src.y=151;}
    // à
    if(val==-32) {src.x=148;src.y=84;}
    // â
    if(val==-30) {src.x=148;src.y=103;}
    // ä
    if(val==-28) {src.x=148;src.y=135;}
    // î
    if(val==-18) {src.x=84;src.y=119;}
    // ï
    if(val==-17) {src.x=116;src.y=151;}
    // û
    if(val==-5) {src.x=84;src.y=103;}
    // ù
    if(val==-7) {src.x=148;src.y=151;}
    // ü
    if(val==-4) {src.x=116;src.y=135;}
    // ö
    if(val==-10) {src.x=132;src.y=135;}
    // ô
    if(val==-12) {src.x=148;src.y=119;}
            
    //ponctuation
    // -
    if(val==45) {src.x=102;src.y=34;}
    // .
    if(val==46) {src.x=118;src.y=34;}
    // ,
    if(val==44) {src.x=134;src.y=34;}
    // !
    if(val==33) {src.x=3;src.y=135;}
    // ?
    if(val==63) {src.x=19;src.y=135;}
    // (
    if(val==40) {src.x=35;src.y=135;}
    // )
    if(val==41) {src.x=51;src.y=135;}            
    // ' ( avec @ )
    if(val==39) {src.x=67;src.y=135;}
    // :
    if(val==58) {src.x=83;src.y=135;}
    // ... ( avec % )
    if(val==37) {src.x=101;src.y=135;}
    // >
    if(val==62) {src.x=100;src.y=151;}
    // <
    if(val==60) {src.x=84;src.y=151;}
            
    //chiffres            
    if(val>=48 && val<=57) {src.x=3+16*((val-48)%5); src.y=103+16*((val-48)/5);}
    
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
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
