// =======================================================
var idMk = charIDToTypeID( "Mk  " );
    var desc20 = new ActionDescriptor();
    var idnull = charIDToTypeID( "null" );
        var ref12 = new ActionReference();
        var idlayerSection = stringIDToTypeID( "layerSection" );
        ref12.putClass( idlayerSection );
    desc20.putReference( idnull, ref12 );
executeAction( idMk, desc20, DialogModes.NO );

// =======================================================
var idslct = charIDToTypeID( "slct" );
    var desc21 = new ActionDescriptor();
    var idnull = charIDToTypeID( "null" );
        var ref13 = new ActionReference();
        var idLyr = charIDToTypeID( "Lyr " );
        ref13.putName( idLyr, "ͼ??1" );
    desc21.putReference( idnull, ref13 );
    var idMkVs = charIDToTypeID( "MkVs" );
    desc21.putBoolean( idMkVs, false );
executeAction( idslct, desc21, DialogModes.NO );

// =======================================================
var idslct = charIDToTypeID( "slct" );
    var desc22 = new ActionDescriptor();
    var idnull = charIDToTypeID( "null" );
        var ref14 = new ActionReference();
        var idLyr = charIDToTypeID( "Lyr " );
        ref14.putName( idLyr, "ͼ??3" );
    desc22.putReference( idnull, ref14 );
    var idselectionModifier = stringIDToTypeID( "selectionModifier" );
    var idselectionModifierType = stringIDToTypeID( "selectionModifierType" );
    var idaddToSelectionContinuous = stringIDToTypeID( "addToSelectionContinuous" );
    desc22.putEnumerated( idselectionModifier, idselectionModifierType, idaddToSelectionContinuous );
    var idMkVs = charIDToTypeID( "MkVs" );
    desc22.putBoolean( idMkVs, false );
executeAction( idslct, desc22, DialogModes.NO );

// =======================================================
var idmove = charIDToTypeID( "move" );
    var desc23 = new ActionDescriptor();
    var idnull = charIDToTypeID( "null" );
        var ref15 = new ActionReference();
        var idLyr = charIDToTypeID( "Lyr " );
        var idOrdn = charIDToTypeID( "Ordn" );
        var idTrgt = charIDToTypeID( "Trgt" );
        ref15.putEnumerated( idLyr, idOrdn, idTrgt );
    desc23.putReference( idnull, ref15 );
    var idT = charIDToTypeID( "T   " );
        var ref16 = new ActionReference();
        var idLyr = charIDToTypeID( "Lyr " );
        ref16.putIndex( idLyr, 5 );
    desc23.putReference( idT, ref16 );
    var idAdjs = charIDToTypeID( "Adjs" );
    desc23.putBoolean( idAdjs, false );
executeAction( idmove, desc23, DialogModes.NO );

// =======================================================
var idHd = charIDToTypeID( "Hd  " );
    var desc24 = new ActionDescriptor();
    var idnull = charIDToTypeID( "null" );
        var list1 = new ActionList();
            var ref17 = new ActionReference();
            var idLyr = charIDToTypeID( "Lyr " );
            ref17.putName( idLyr, "ͼ??0" );
        list1.putReference( ref17 );
    desc24.putList( idnull, list1 );
executeAction( idHd, desc24, DialogModes.NO );

// =======================================================
var idsave = charIDToTypeID( "save" );
    var desc25 = new ActionDescriptor();
    var idAs = charIDToTypeID( "As  " );
        var desc26 = new ActionDescriptor();
        var idPGIT = charIDToTypeID( "PGIT" );
        var idPGIT = charIDToTypeID( "PGIT" );
        var idPGIN = charIDToTypeID( "PGIN" );
        desc26.putEnumerated( idPGIT, idPGIT, idPGIN );
        var idPNGf = charIDToTypeID( "PNGf" );
        var idPNGf = charIDToTypeID( "PNGf" );
        var idPGAd = charIDToTypeID( "PGAd" );
        desc26.putEnumerated( idPNGf, idPNGf, idPGAd );
    var idPNGF = charIDToTypeID( "PNGF" );
    desc25.putObject( idAs, idPNGF, desc26 );
    var idIn = charIDToTypeID( "In  " );
    desc25.putPath( idIn, new File( "C:\\Users\\tsinglee\\Desktop\\20?ſ??_1.png" ) );
    var idCpy = charIDToTypeID( "Cpy " );
    desc25.putBoolean( idCpy, true );
executeAction( idsave, desc25, DialogModes.NO );

