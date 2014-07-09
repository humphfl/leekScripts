//{
//##############################################################
//#                         GLOBALS                            #
//##############################################################
global turn = 0;
global myChips = getChips();
global mychipsCd = [];
global CAT_ATK = "atk";
global CAT_DEF = "def";
global CAT_BUF = "buf";
global CAT_VIE = "vie";
global CAT_DEBUF = "debuf";

//}
//{
//##############################################################
//#                         DATA TYPE                          #
//##############################################################
/**
 * renvoie l'élément qui a pour clé key
 **/
function getItem(key, dict) {
	for (var item in dict) {
		if (inArray(item, key)) {
			return item[1];
		}
	}
	return null;
}

/**
 * supprime l'élément qui a la clé key
 **/
function deleteItem(key, dict) {
	for (var i = 0; i < count(dict); i++) {
		if (inArray(dict[i], key)) {
			remove(dict, i);
			return 1;
		}
	}
	return -1;
}

/**
 * ajoute un élément qui a pour clé key et valeur value
 **/
function setItem(key, value, dict) {
	deleteItem(key, dict);
	push(dict, [key, value]);
}

//}
//{
//##############################################################
//#                         FUNCTIONS                          #
//##############################################################
/**
* renvoie les effets d'uner arme :
* [min_range, max_range, min_damage, max_damage, shotSCost, isEquiped, rangeType, specialEffects]
* 0 : portée min
* 1 : portée max
* 2 : dégats min
* 3 : dégats max
* 4 : cout du tir
* 5 : arme équipée ? 
* 6 : portée normale ou en ligne
* 7 : autres effets
**/
function myGetWeaponEffects(weapon){
	if(weapon==WEAPON_PISTOL){
		var isEquiped = false;
		if(getWeapon()==weapon){isEquiped=true;}
		return[/*min_range*/0, /*max_range*/7, /*min_damage*/15, /*max_damage*/20,
			   /*shotCost*/3, /*isEquiped*/isEquiped, /*rangeType*/RANGE_NORMAL, 
			   /*special*/[]];
	}
}
/**
 * renvoie les effets d'une chip :
 * [Curent_cd, max_cd, min_range, max_range, cat, minDamage/heal/bouclier, maxDamage/bouclier/heal, fail_rate, cost]
 * 0 : cooldown actuel
 * 1 : cooldown total
 * 2 : portée minimum
 * 3 : portée maximum
 * 4 : catégorie
 * 5 : plage de dégats/heal/bouclier minimum
 * 6 : plage de dégats/heal/bouclier maximum
 * 7 : taux d'échec
 * 8 : cout en PT
 * 9 : portée normale ou en ligne (à ajouter)
 * 10: autre effets (à ajouter)
 **/
function myGetChipEffects(chip) {
	if (chip == CHIP_BANDAGE) {
		return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/1, /*minRange*/0, 
				/*maxRange*/6,/*cat*/CAT_VIE ,/*min*/10,/*max*/ 15, 
				/*fail*/0.05,/*cost*/ 2];
	}
	if (chip == CHIP_CURE) {
		return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/2, /*minRange*/0, 
				/*maxRange*/5,/*cat*/CAT_VIE ,/*min*/35,/*max*/ 53, 
				/*fail*/0.08,/*cost*/ 4];
	}
	if (chip == CHIP_DRIP) {
		return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/3, /*minRange*/2, 
				/*maxRange*/6,/*cat*/CAT_VIE ,/*min*/35,/*max*/ 40, 
				/*fail*/0.07,/*cost*/ 5];
	} //zone
	if (chip == CHIP_VACCINE) {
		return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/3, /*minRange*/0, 
				/*maxRange*/6,/*cat*/CAT_VIE ,/*min*/30,/*max*/ 32, 
				/*fail*/0.07,/*cost*/ 6];
	}
	if (chip == CHIP_RESURRECTION) {
		return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/64, /*minRange*/0, 
				/*maxRange*/3,/*cat*/CAT_VIE ,/*min*/200,/*max*/ 200, 
				/*fail*/0.25,/*cost*/ 8];
	} //ressusiter
	
	if (chip == CHIP_STRETCHING) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/3, /*minRange*/0, 
				/*maxRange*/5,/*cat*/CAT_BUF ,/*min*/50,/*max*/ 50, 
				/*fail*/0.05,/*cost*/ 3];
	} //+agi
	if (chip == CHIP_PROTEIN) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/3, /*minRange*/0, 
				/*maxRange*/4,/*cat*/CAT_BUF ,/*min*/50,/*max*/ 50, 
				/*fail*/0.06,/*cost*/ 3];
	} //+force
	if (chip == CHIP_MOTIVATION) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/3, /*minRange*/0, 
				/*maxRange*/5,/*cat*/CAT_BUF ,/*min*/1,/*max*/ 1, 
				/*fail*/0.06,/*cost*/ 3];
	} //+PT
	if (chip == CHIP_LEATHER_BOOTS) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/3, /*minRange*/0, 
				/*maxRange*/5,/*cat*/CAT_BUF ,/*min*/1,/*max*/ 1, 
				/*fail*/0.05,/*cost*/ 3];
	} //+PM
	if (chip == CHIP_STEROID) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/4, /*minRange*/0, 
				/*maxRange*/4,/*cat*/CAT_BUF ,/*min*/100,/*max*/ 100, 
				/*fail*/0.05,/*cost*/ 6];
	} //+force
	if (chip == CHIP_WARM_UP) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/4, /*minRange*/0, 
				/*maxRange*/4,/*cat*/CAT_BUF ,/*min*/100,/*max*/ 100, 
				/*fail*/0.08,/*cost*/ 6];
	} //+agi
	if (chip == CHIP_WINGED_BOOTS) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/4, /*minRange*/0, 
				/*maxRange*/3,/*cat*/CAT_BUF ,/*min*/1,/*max*/ 1, 
				/*fail*/0.10,/*cost*/ 4];
	} //+PM zone
	if (chip == CHIP_ADRENALINE) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/4, /*minRange*/0, 
				/*maxRange*/5,/*cat*/CAT_BUF ,/*min*/1,/*max*/ 1, 
				/*fail*/0.08,/*cost*/ 5];
	} //+PT zone
	if (chip == CHIP_REFLEXES) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/5, /*minRange*/0, 
				/*maxRange*/3,/*cat*/CAT_BUF ,/*min*/200,/*max*/ 200, 
				/*fail*/0.06,/*cost*/ 8];
	} //+agi
	if (chip == CHIP_DOPING) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/5, /*minRange*/0, 
				/*maxRange*/5,/*cat*/CAT_BUF ,/*min*/200,/*max*/ 200, 
				/*fail*/0.14,/*cost*/ 7];
	} //+force
	if (chip == CHIP_SEVEN_LEAGUE_BOOTS) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/5, /*minRange*/0, 
				/*maxRange*/2,/*cat*/CAT_BUF ,/*min*/2,/*max*/ 4, 
				/*fail*/0.07,/*cost*/ 6];
	} //+PM
	if (chip == CHIP_RAGE) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/5, /*minRange*/0, 
				/*maxRange*/3,/*cat*/CAT_BUF ,/*min*/2,/*max*/ 4, 
				/*fail*/0.12,/*cost*/ 7];
	} //+PT
	
	if (chip == CHIP_LIBERATION) {
		return CAT_DEBUF;
	}
	
	if (chip == CHIP_HELMET) {
		return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/4, /*minRange*/0, 
				/*maxRange*/4,/*cat*/CAT_DEF ,/*min*/15,/*max*/ 15, 
				/*fail*/0.10,/*cost*/ 4]; //+flat
	}
	if (chip == CHIP_WALL) {
		return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/5, /*minRange*/0, 
				/*maxRange*/3,/*cat*/CAT_DEF ,/*min*/0.15,/*max*/ 0.15, 
				/*fail*/0.06,/*cost*/ 4]; //+rel
	}
	if (chip == CHIP_SHIELD) {
		return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/3, /*minRange*/0, 
				/*maxRange*/4,/*cat*/CAT_DEF ,/*min*/8,/*max*/ 8, 
				/*fail*/0.05,/*cost*/ 3]; //+flat
	}
	if (chip == CHIP_RAMPART) {
		return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/4, /*minRange*/2, 
				/*maxRange*/7,/*cat*/CAT_DEF ,/*min*/0.25,/*max*/ 0.25, 
				/*fail*/0.05,/*cost*/ 6]; //+rel
	}
	if (chip == CHIP_ARMOR) {
		return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/5, /*minRange*/0, 
				/*maxRange*/4,/*cat*/CAT_DEF ,/*min*/25,/*max*/ 25, 
				/*fail*/0.08,/*cost*/ 6]; //+flat
	}
	if (chip == CHIP_FORTRESS) {
		return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/4, /*minRange*/0, 
				/*maxRange*/3,/*cat*/CAT_DEF ,/*min*/0.40,/*max*/ 0.40, 
				/*fail*/0.06,/*cost*/ 8]; //+rel
	}
	
	if (chip == CHIP_SHOCK) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/0, /*minRange*/0, 
				/*maxRange*/6,/*cat*/CAT_ATK ,/*min*/5,/*max*/ 7, 
				/*fail*/0.30,/*cost*/ 2];
	} //zone
	}
	if (chip == CHIP_PEBBLE) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/1, /*minRange*/0, 
				/*maxRange*/5,/*cat*/CAT_ATK ,/*min*/2,/*max*/ 17, 
				/*fail*/0.09,/*cost*/ 2];
	} //zone
	}
	if (chip == CHIP_SPARK) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/3, /*minRange*/0, 
				/*maxRange*/10,/*cat*/CAT_ATK ,/*min*/8,/*max*/ 16, 
				/*fail*/0.04,/*cost*/ 3];
	} //zone
	} //passe au travers des obstacles
	if (chip == CHIP_ICE) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/0, /*minRange*/0, 
				/*maxRange*/8,/*cat*/CAT_ATK ,/*min*/17,/*max*/ 19, 
				/*fail*/0.05,/*cost*/ 4];
	} //zone
	}
	if (chip == CHIP_ROCK) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/1, /*minRange*/2, 
				/*maxRange*/6,/*cat*/CAT_ATK ,/*min*/30,/*max*/ 31, 
				/*fail*/0.08,/*cost*/ 5];
	} //zone
	}
	if (chip == CHIP_FLASH) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/1, /*minRange*/1, 
				/*maxRange*/7,/*cat*/CAT_ATK ,/*min*/19,/*max*/ 24, 
				/*fail*/0.01,/*cost*/ 4];
	} //zone
	} //zone
	if (chip == CHIP_FLAME) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/0, /*minRange*/2, 
				/*maxRange*/7,/*cat*/CAT_ATK ,/*min*/25,/*max*/ 27, 
				/*fail*/0.10,/*cost*/ 4];
	} //zone
	}
	if (chip == CHIP_STALACTITE) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/3, /*minRange*/2, 
				/*maxRange*/7,/*cat*/CAT_ATK ,/*min*/64,/*max*/ 67, 
				/*fail*/0.20,/*cost*/ 6];
	} //zone
	}
	if (chip == CHIP_LIGHTNING) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/0, /*minRange*/2, 
				/*maxRange*/6,/*cat*/CAT_ATK ,/*min*/35,/*max*/ 47, 
				/*fail*/0.07,/*cost*/ 4];
	} //zone
	if (chip == CHIP_ROCKFALL) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/1, /*minRange*/5, 
				/*maxRange*/7,/*cat*/CAT_ATK ,/*min*/48,/*max*/ 56, 
				/*fail*/0.08,/*cost*/ 7];
	} //zone
	if (chip == CHIP_ICEBERG) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/3, /*minRange*/3, 
				/*maxRange*/5,/*cat*/CAT_ATK ,/*min*/72,/*max*/ 80, 
				/*fail*/0.05,/*cost*/ 7];
	} //zone
	if (chip == CHIP_METEORITE) {
	return [/*actual cd*/getItem(chip, mychipsCd), /*cd*/3, /*minRange*/4, 
				/*maxRange*/8,/*cat*/CAT_ATK ,/*min*/70,/*max*/ 80, 
				/*fail*/0.04,/*cost*/ 8];
	} //zone
}
/**
* fonction d'initialisation du tour
**/
function initTurn() {
	//Mise à jour du tour
	turn++;
	//Mise à jour des cooldowns
	var value = 0;
	for(var chip in myChips){
		value = max(0, getItem(chip, mychipsCd)-1);
		setItem(chip, value, mychipsCd);
	}
}

/**
* fonction d'initialisation de la partie
**/
function initGame() {
	for(var chip in myChips){
		setItem(chip, 0, mychipsCd);
	}

}

//}
//{
//##############################################################
//#                            MAIN                            #
//##############################################################
initTurn();
if(turn=1){initGame();}
debug("##############################");

//}